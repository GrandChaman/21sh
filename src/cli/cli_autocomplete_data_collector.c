/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete_data_collector.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:57:29 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/18 14:15:43 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	cmp_autoc_entry(void *e1, void *e2)
{
	return (ft_strcmp(((t_ft_autoc_entry*)e1)->name,
		((t_ft_autoc_entry*)e2)->name));
}

static void	get_graphics_for_filetype(mode_t type, t_ft_autoc_entry *entry)
{
	entry->undeline = 0;
	if ((type & S_IFMT) == S_IFDIR)
		entry->color = ANSI_COLOR_B_RED;
	else if ((type & S_IFMT) == S_IFCHR)
		entry->color = ANSI_COLOR_CYAN;
	else if ((type & S_IFMT) == S_IFLNK)
	{
		entry->color = ANSI_COLOR_GREEN;
		entry->undeline = 1;
	}
	else
		entry->color = "";
}

static void	load_dir_autocomplete(DIR *dir, t_list **list, char *path, char *str_part)
{
	size_t				len;
	struct dirent		*dir_data;
	t_ft_autoc_entry	entry;
	struct stat			stat_buf;
	char				*fpath;

	len = 0;
	if (str_part)
		len = ft_strlen(str_part);
	while ((dir_data = readdir(dir)))
	{
		if (str_part && ft_strncmp(dir_data->d_name, str_part, len))
			continue ;
		ft_asprintf(&fpath, "%s/%s", path, dir_data->d_name);
		if (!stat(fpath, &stat_buf))
			get_graphics_for_filetype(stat_buf.st_mode, &entry);
		free(fpath);
		entry.name = ft_strdup(dir_data->d_name);
		ft_lstpush_back(list, &entry, sizeof(t_ft_autoc_entry));
	}
}

static void	collect_data_local_file(t_list **list, char *str_part)
{
	DIR					*dir;
	char				*path;
	char				*slash;

	dir = NULL;
	path = NULL;
	slash = NULL;
	if ((dir = opendir(str_part)))
	{
		ft_fprintf(get_ft_shell()->debug_tty, "HERE 1\n");
		load_dir_autocomplete(dir, list, str_part, NULL);
	}
	else if (str_part && (slash = ft_strrchr(str_part, '/')))
	{
		path = ft_strndup(str_part, (slash - str_part) + 1);
		ft_fprintf(get_ft_shell()->debug_tty, "HERE 2 : %s\n", slash);
		if ((dir = opendir(path)))
			load_dir_autocomplete(dir, list, str_part, slash + 1);
		else
			ft_free((void**)&path);
	}
	if (!dir && !path)
	{
		path = ft_getcwd();
		ft_fprintf(get_ft_shell()->debug_tty, "HERE 3 : %s\n", path);
		if ((dir = opendir(path)))
			load_dir_autocomplete(dir, list, path,
				(str_part && str_part[0] ? str_part : NULL));
	}
	closedir(dir);
	free(path);
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
	exec_term_command_p(TC_MOVENUP, 0, i - 1);
	sh->cursor = sh->buf.cursor;
	exec_term_command_p(TC_MOVENRIGHT, 0, (sh->prompt_size +
		cursor_new_origin(sh)) % sh->x_size);
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
	//ft_lstforeach(sh->autocomplete, debug_autocomplete);
}
