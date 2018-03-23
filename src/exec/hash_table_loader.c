/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_loader.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:16:18 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/23 20:35:50 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

unsigned long			dj2b_hash(char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}

void					free_hash_table(t_bin_hash_table **ht)
{
	unsigned int i;

	i = 0;
	if (!ht || !*ht)
		return ;
	while (i < (*ht)->size)
	{
		free((*ht)->table[i].name);
		free((*ht)->table[i].path);
		i++;
	}
	free((*ht)->table);
	free((*ht));
	*ht = 0;
}

static void				list_file_in_dir(t_list **list, char *path)
{
	DIR				*dir;
	struct dirent	*dir_data;
	struct stat		st_data;
	t_bin_hash		bin;
	size_t			path_len;

	if (!path || !(dir = opendir(path)))
		return ;
	path_len = ft_strlen(path);
	while ((dir_data = readdir(dir)))
	{
		bin.name = ft_strdup(dir_data->d_name);
		bin.path = ft_strnew(path_len + dir_data->d_namlen + 2);
		ft_snprintf(bin.path, path_len + dir_data->d_namlen + 2, "%s/%s", path,
			dir_data->d_name);
		if (stat(bin.path, &st_data) || ((st_data.st_mode & S_IFMT) != S_IFREG
			&& (st_data.st_mode & S_IFMT) != S_IFLNK))
		{
			free(bin.name);
			free(bin.path);
			continue ;
		}
		bin.can_exec = !access(bin.path, X_OK);
		ft_lstpush_back(list, &bin, sizeof(t_bin_hash));
	}
	closedir(dir);
}

static t_bin_hash_table	*fill_hash_table_form_list(t_list **list)
{
	t_bin_hash_table	*res;
	t_list				*tmp;
	unsigned int		index;

	res = ft_memalloc(sizeof(t_bin_hash_table));
	res->size = ft_lstsize(*list);
	res->table = ft_memalloc(sizeof(t_bin_hash) * res->size);
	tmp = *list;
	while (tmp)
	{
		index = dj2b_hash(((t_bin_hash*)tmp->content)->name) % res->size;
		while (res->table[index % res->size].path)
			index++;
		res->table[index % res->size].path = ((t_bin_hash*)tmp->content)->path;
		res->table[index % res->size].name = ((t_bin_hash*)tmp->content)->name;
		res->table[index % res->size].can_exec =
			((t_bin_hash*)tmp->content)->can_exec;
		tmp = tmp->next;
	}
	ft_lstdel(list, NULL);
	return (res);
}

t_bin_hash_table		*load_bin_into_hash_table(t_list *env)
{
	t_list		*tmp;
	char		*tmp_path;
	char		*path;
	int			offset;

	if (!(tmp = ft_lstfind(env, "PATH", compare_with_key)))
		return (NULL);
	path = ((t_env_var*)tmp->content)->value;
	tmp = NULL;
	while ((tmp_path = ft_strchr(path, ':')) || 1)
	{
		if (!tmp_path)
		{
			list_file_in_dir(&tmp, path);
			break ;
		}
		offset = (int)(tmp_path - path) + 1;
		tmp_path = ft_strsub(path, 0, (int)(tmp_path - path));
		path += offset;
		list_file_in_dir(&tmp, tmp_path);
		free(tmp_path);
	}
	return (fill_hash_table_form_list(&tmp));
}
