/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete_local_file.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 16:40:02 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/18 17:06:22 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

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

void	collect_data_local_file(t_list **list, char *str_part)
{
	DIR					*dir;
	char				*path;
	char				*slash;

	path = NULL;
	slash = NULL;
	if ((dir = opendir(str_part)))
		load_dir_autocomplete(dir, list, str_part, NULL);
	else if (str_part && (slash = ft_strrchr(str_part, '/')))
	{
		path = ft_strndup(str_part, (slash - str_part) + 1);
		if ((dir = opendir(path)))
			load_dir_autocomplete(dir, list, str_part, slash + 1);
		else
			ft_free((void**)&path);
	}
	if (!dir && !path)
	{
		path = ft_getcwd();
		if ((dir = opendir(path)))
			load_dir_autocomplete(dir, list, path,
				(str_part && str_part[0] ? str_part : NULL));
	}
	closedir(dir);
	free(path);
}
