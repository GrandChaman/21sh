/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete_data_collector.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:57:29 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/15 17:54:41 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	cmp_autoc_entry(void *e1, void *e2)
{
	return (ft_strcmp(((t_ft_autoc_entry*)e1)->name,
		((t_ft_autoc_entry*)e2)->name));
}

static void	collect_data_local_file(t_btree **tree, char *str_part)
{
	DIR					*dir;
	struct dirent		*dir_data;
	char				*path;
	t_ft_autoc_entry	*entry;

	if (!str_part)
		path = ft_getcwd();
	else
		path = NULL;
	if (!(dir = opendir(str_part ? str_part : path)))
	{
		free(path);
		return ;
	}
	while ((dir_data = readdir(dir)))
	{
		entry = ft_memalloc(sizeof(t_ft_autoc_entry));
		entry->name = ft_strdup(dir_data->d_name);
		entry->color = ANSI_COLOR_YELLOW;
		entry->undeline = 0;
		entry->inverted = 0;
		ft_btree_insert_data(tree, entry, cmp_autoc_entry);
	}
	closedir(dir);
	free(path);
}

void debug_autocomplete(void *print)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	ft_fprintf(sh->debug_tty, "%s%s{eoc} - %d - %d\n", ((t_ft_autoc_entry*)print)->color,
	((t_ft_autoc_entry*)print)->name, ((t_ft_autoc_entry*)print)->undeline, ((t_ft_autoc_entry*)print)->inverted);
	free(((t_ft_autoc_entry*)print)->name);
}

static int			get_el_with(t_btree *tree, int min)
{
	int res;

	res = ft_strlen(((t_ft_autoc_entry*)tree->item)->name);
	res = (res < min ? min : res);
	if (tree->left)
		res = get_el_with(tree->left, res);
	if (tree->right)
		res = get_el_with(tree->right, res);
	return (res);
}

void		prepare_autocomplete(t_ft_sh *sh, t_btree *tree, unsigned int save_cur)
{
	int		el_width;
	int		len;
	int		nb_per_line;
	int		nb_lines;
	int		i;

	el_width = get_el_with(tree, 0) + 7;
	len = ft_btree_count_node(tree);
	nb_per_line = sh->x_size / el_width;
	nb_lines = 0;
	while (nb_lines * nb_per_line < len)
		nb_lines++;
	while (sh->cursor < sh->buf.cursor)
		move_in_terminal(T_RARR, 1);
	i = 0;
	while (i++ < nb_lines)
		ft_putchar('\n');
	ft_fprintf(sh->debug_tty, "NB : %d\nWIDTH : %d\nNB_PER_LINE : %d\nNB_LINES : %d\n", len, el_width, nb_per_line, nb_lines);
	exec_term_command_p(TC_MOVENUP, 0, i - 1);
	sleep(1);
	exec_term_command_p(TC_MOVENRIGHT, 0, (sh->prompt_size +
		cursor_new_origin(sh)) % sh->x_size);
	sleep(1);
	sh->cursor = sh->buf.cursor;
	while (sh->cursor > save_cur)
		move_in_terminal(T_LARR, 1);
}

t_btree		*collect_data(char *str_part)
{
	t_btree				*tree;
	t_ft_sh *sh;
	unsigned int save_cur;

	sh = get_ft_shell();
	save_cur = sh->cursor;
	tree = NULL;
	ft_fprintf(sh->debug_tty, "STRPART : %s\n", str_part);
	collect_data_local_file(&tree, str_part);
	ft_btree_apply_prefix(tree, debug_autocomplete);
	prepare_autocomplete(sh, tree, save_cur);
	ft_btree_destroy(&tree);
	return (NULL);
}
