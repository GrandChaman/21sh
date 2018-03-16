/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete_data_collector.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:57:29 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/16 14:37:10 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	cmp_autoc_entry(void *e1, void *e2)
{
	return (ft_strcmp(((t_ft_autoc_entry*)e1)->name,
		((t_ft_autoc_entry*)e2)->name));
}

static void	collect_data_local_file(t_list **list, char *str_part)
{
	DIR					*dir;
	struct dirent		*dir_data;
	char				*path;
	t_ft_autoc_entry	entry;

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
		entry.name = ft_strdup(dir_data->d_name);
		entry.color = ANSI_COLOR_YELLOW;
		entry.undeline = 0;
		entry.inverted = 0;
		ft_lstpush_back(list, &entry, sizeof(t_ft_autoc_entry));
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
}

static int			get_el_with(t_list *list)
{
	int res;
	int tmp;

	res = 0;
	while (list)
	{
		tmp = ft_strlen(((t_ft_autoc_entry*)list->content)->name);
		if (res < tmp)
			res = tmp;
		list = list->next;
	}
	return (res);
}

void		setpos_autocomplete(t_ft_sh *sh)
{
	unsigned int x;
	unsigned int y;
	t_list *list;

	list = sh->autocomplete;
	x = 0;
	y = 0;
	while (list)
	{
		ft_fprintf(sh->debug_tty, "AUTOC : (%d,%d) / %d - %d\n", x * sh->autocomplete_padding, y, (x + 1) * sh->autocomplete_padding, sh->x_size);
		((t_ft_autoc_entry*)list->content)->x_pos = x *
			sh->autocomplete_padding;
		((t_ft_autoc_entry*)list->content)->y_pos = y;
		if ((x + 2) * sh->autocomplete_padding > sh->x_size)
		{
			x = 0;
			y++;
		}
		else
			x++;
		list= list->next;
	}
}


void		prepare_autocomplete(t_ft_sh *sh, t_list *list, unsigned int save_cur)
{
	int		len;
	int		nb_per_line;
	int		nb_lines;
	int		i;

	sh->autocomplete_padding = get_el_with(list) + 7;
	len = ft_lstsize(list);
	nb_per_line = sh->x_size / sh->autocomplete_padding;
	nb_lines = (len / nb_per_line) + 1;
	while (sh->cursor < sh->buf.cursor)
		move_in_terminal(T_RARR, 1);
	i = 0;
	while (i++ < nb_lines)
		ft_putchar('\n');
	ft_fprintf(sh->debug_tty, "NB : %d\nWIDTH : %d\nNB_PER_LINE : %d\nNB_LINES : %d\n", len, sh->autocomplete_padding, nb_per_line, nb_lines);
	exec_term_command_p(TC_MOVENUP, 0, i - 1);
	exec_term_command_p(TC_MOVENRIGHT, 0, (sh->prompt_size +
		cursor_new_origin(sh)) % sh->x_size);
	sh->cursor = sh->buf.cursor;
	while (sh->cursor > save_cur)
		move_in_terminal(T_LARR, 1);
	setpos_autocomplete(sh);
}

void		collect_data(char *str_part)
{
	t_ft_sh *sh;
	unsigned int save_cur;

	sh = get_ft_shell();
	save_cur = sh->cursor;
	ft_fprintf(sh->debug_tty, "STRPART : %s\n", str_part);
	collect_data_local_file(&sh->autocomplete, str_part);
	ft_lstsort(&sh->autocomplete, cmp_autoc_entry);
	ft_lstforeach(sh->autocomplete, debug_autocomplete);
	prepare_autocomplete(sh, sh->autocomplete, save_cur);
}
