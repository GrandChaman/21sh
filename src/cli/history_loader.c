/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:16:25 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/06 15:18:35 by fle-roy          ###   ########.fr       */
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

static int read_history(t_ft_sh *sh, int fd)
{
	int				gnl_res;
	t_dbuf			dbuf;
	char			*line;
	char			*tmp;
	t_ft_hist_entry entry;

	dbuf_init(&dbuf);
	while ((gnl_res = get_next_line(fd, &line)) > 0
		&& sh->history_size < SH_HIST_MAX_SIZE)
	{
		dbuf_append(&dbuf, line);
		free(line);
		if (check_correct(dbuf.buf) && dbuf_append(&dbuf, "\n") == LIBFT_OK)
			continue ;
		if ((tmp = ft_strchr(dbuf.buf, ' ')) && tmp[1])
		{
			tmp++;
			entry.command = ft_strdup(tmp);
			entry.timestamp = ft_atoi(dbuf.buf);
			ft_fprintf(sh->debug_tty, "Added : %s\n", entry.command);
			ft_lstpush_front(&sh->history, &entry, sizeof(entry));
			sh->history_size++;
		}
		dbuf_clear(&dbuf);
	}
	dbuf_destroy(&dbuf);
	close(fd);
	while (get_next_line(fd, &line) > 0)
		free(line);
	return ((gnl_res >= 0 ? 0 : -1));
}

static void write_history(t_ft_sh *sh, int fd)
{
	t_ft_hist_entry *entry;
	t_list			*list;

	list = ft_lstat(sh->history, sh->history_size - 1 > SH_HIST_MAX_SIZE - 1? SH_HIST_MAX_SIZE - 1: sh->history_size - 1);
		ft_fprintf(sh->debug_tty, "Len : %d, pointer : %p, pos : %d\n", sh->history_size, list, sh->history_size - 1 > SH_HIST_MAX_SIZE ? SH_HIST_MAX_SIZE : sh->history_size - 1);
	while (list)
	{
		entry = (t_ft_hist_entry*)list->content;
		ft_fprintf(fd, "%d %s\n", entry->timestamp, entry->command);
		ft_fprintf(sh->debug_tty, "Writing %d %s\n", entry->timestamp, entry->command);
		list = list->prev;
	}
	ft_lstdel(&sh->history, delete_hist_entry);
	sh->history_size = 0;
	sh->history_pos = -1;
}

int load_history(t_ft_sh *sh, int unload)
{
	char	*path;
	char	*home;
	int		res;
	int		fd;

	if (!unload)
	{
		sh->history = NULL;
		sh->history_size = 0;
		sh->history_pos = -1;
		sh->history_last = NULL;
	}
	if (!(home = getenv("HOME")))
		return (ft_fprintf(2, "\nCan't open history file. $HOME's not defined\n"));
	path = ft_strjoin(home, "/.21sh_history");
	if ((fd = open(path, (unload ? O_WRONLY : O_RDONLY) | O_CREAT | (unload ? O_TRUNC : 0), 0600)) < 0)
		return (ft_fprintf(2, "\nCan't open history file. open() failed.\n"));
	if (unload)
	{
		write_history(sh, fd);
		close(fd);
	}
	else if ((res = read_history(sh, fd)))
	{
		ft_fprintf(2, "\nCan't read history file.\n");
		ft_lstdel(&sh->history, delete_hist_entry);
	}
	free(path);
	return (unload ? 0 : res);
}

void	add_to_history(t_ft_sh *sh, char *cmd)
{
	t_ft_hist_entry entry;

	if (!cmd || !ft_strlen(cmd))
		return ;
	entry.command = ft_strdup(cmd);
	entry.timestamp = time(NULL);
	ft_lstpush_front(&sh->history, &entry, sizeof(entry));
	sh->history_size++;
}
