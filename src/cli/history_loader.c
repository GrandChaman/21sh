/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:16:25 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/01 13:50:21 by fle-roy          ###   ########.fr       */
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
	while ((gnl_res = get_next_line(fd, &line)) > 0)
	{
		dbuf_append(&dbuf, line);
		free(line);
		if (check_correct(dbuf.buf) && dbuf_append(&dbuf, "\n") == LIBFT_OK)
			continue ;
		if ((tmp = ft_strchr(dbuf.buf, ' ')))
		{
			tmp++;
			entry.command = ft_strdup((tmp ? tmp : "(null)"));
			entry.timestamp = ft_atoi(dbuf.buf);
			ft_lstpush_back(&sh->history, &entry, sizeof(entry));
			sh->history_size++;
		}
		dbuf_clear(&dbuf);
	}
	dbuf_destroy(&dbuf);
	return (gnl_res);
}

static void write_history(t_ft_sh *sh, int fd)
{
	t_ft_hist_entry *entry;
	t_list			*list;
	int i;
	int len;

	i = 0;
	len = ft_lstsize(sh->history);
	if (len > SH_HIST_MAX_SIZE)
		i = len - SH_HIST_MAX_SIZE;
	list = ft_lstat(sh->history, i);
	while (list)
	{
		entry = (t_ft_hist_entry*)list->content;
		ft_fprintf(sh->debug_tty, "\nIn function : %s.\n", entry->command);
		ft_fprintf(fd, "%d %s\n", entry->timestamp, entry->command);
		list = list->next;
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

	if (!unload)
	{
		sh->history = NULL;
		sh->history_size = 0;
	}
	if (!(home = getenv("HOME")))
		return (ft_fprintf(2, "\nCan't open history file. $HOME's not defined\n"));
	path = ft_strjoin(home, "/.21sh_history");
	if ((fd = open(path, O_RDWR | O_CREAT | (unload ? O_TRUNC : 0), 0600)) < 0)
		return (ft_fprintf(2, "\nCan't open history file. open() failed.\n"));
	if (unload)
		write_history(sh, fd);
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

	if (!cmd || !ft_strlen(cmd))
		return ;
	entry.command = ft_strdup(cmd);
	entry.timestamp = time(NULL);
	while (sh->history_size-- >= SH_HIST_MAX_SIZE)
	{
		ft_fprintf(sh->debug_tty, "\nDeleting : %s.\n", ((t_ft_hist_entry*)sh->history->content)->command);
		ft_lstdelone(&sh->history, delete_hist_entry);
	}
	ft_lstpush_back(&sh->history, &entry, sizeof(entry));
	sh->history_size++;
}
