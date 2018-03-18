/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:16:25 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/18 11:53:35 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	delete_hist_entry(void *entry, size_t size)
{
	t_ft_hist_entry *hentry;

	(void)size;
	hentry = (t_ft_hist_entry*)entry;
	free(hentry->command);
	free(hentry);
}

void	trim_history(t_ft_sh *sh)
{
	int		i;
	t_list	*lcpy;

	i = 0;
	lcpy = sh->history;
	while (i++ < SH_HIST_MAX_SIZE && lcpy)
		lcpy = lcpy->next;
	if (lcpy)
		ft_lstdel(&lcpy, delete_hist_entry);
}

static int read_history(t_ft_sh *sh, int fd)
{
	int				gnl_res;
	char			*line;
	char			*tmp;
	t_ft_hist_entry entry;

	while ((gnl_res = get_next_line(fd, &line)) > 0)
	{
		tmp = ft_strchr(line, ' ');
		if (tmp)
			entry.command = ft_strdup(tmp + 1);
		else
			entry.command = ft_strdup(line);
		entry.timestamp = ft_atoi(line);
		free(line);
		ft_lstpush_front(&sh->history, &entry, sizeof(entry));
		sh->history_size++;
		if (sh->history_size > SH_HIST_MAX_SIZE)
			trim_history(sh);
	}
	return (gnl_res);
}

static void write_history(t_ft_sh *sh, int fd)
{
	t_ft_hist_entry *entry;
	t_list			*list;
	int len;

	len = sh->history_size;
	list = ft_lstat(sh->history,
		(len > SH_HIST_MAX_SIZE ? SH_HIST_MAX_SIZE - 1: len - 1));
	while (list)
	{
		entry = (t_ft_hist_entry*)list->content;
		ft_fprintf(fd, "%d %s\n", entry->timestamp, entry->command);
		list = list->prev;
	}
	ft_lstdel(&sh->history, delete_hist_entry);
	sh->history_size = 0;
}

int load_history(t_ft_sh *sh, int unload)
{
	char	*path;
	char	*home;
	int		res;
	int		fd;

	if (!(home = getenv("HOME")))
		return (ft_fprintf(2, "\nCan't open history file. $HOME's not defined\n"));
	path = ft_strjoin(home, "/.21sh_history");
	if ((fd = open(path, O_RDWR | O_CREAT | (unload ? O_TRUNC : 0), 0600)) < 0)
		return (ft_fprintf(2, "\nCan't open history file. open() failed.\n"));
	if (unload)
	{
		write_history(sh, fd);
		sh->history = NULL;
		sh->history_size = 0;
	}
	else if ((res = read_history(sh, fd)))
	{
		ft_fprintf(2, "\nCan't read history file.\n");
		ft_lstdel(&sh->history, delete_hist_entry);
	}
	close(fd);
	free(path);
	return (unload ? 0 : res);
}

void	add_to_history(t_ft_sh *sh, char *cmd)
{
	t_ft_hist_entry entry;
	int i;
	int last_nl;

	i = 0;
	last_nl = 0;
	if (!cmd || cmd[0] == '\0')
		return ;
	entry.timestamp = time(NULL);
	while (cmd[i++])
		if (cmd[i] == '\n' || !cmd[i])
		{
			entry.command = ft_strsub(cmd, last_nl, i - last_nl);
			ft_lstpush_front(&sh->history, &entry, sizeof(entry));
			sh->history_size++;
			last_nl = i + 1;
		}
	if (sh->history_size > SH_HIST_MAX_SIZE)
		trim_history(sh);
}
