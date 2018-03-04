/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 10:48:18 by bluff             #+#    #+#             */
/*   Updated: 2018/03/04 19:55:36 by bluff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	*search_in_history(char *search, t_ft_sh *sh, int up, int *pos)
{
	t_list *list;
	int		tmp;
	int		i;
	int		max_size;
	int		len;

	len = ft_strlen(search);
	list = ft_lstat(sh->history, sh->history_pos);
	*pos = 0;
	i = 0;
	max_size = 0;
	if (!len)
		return (((t_ft_hist_entry*)ft_lstat(sh->history,
			(up ? sh->history_pos++ : sh->history_pos--))->content)->command);
	while (list)
	{
		if ((tmp = ft_strcommon(((t_ft_hist_entry*)list->content)->command,
		search)) > max_size && ft_strcmp(sh->buf.buf, ((t_ft_hist_entry*)list->content)->command))
		{
			ft_fprintf(sh->debug_tty, "Possible match : %s\n", ((t_ft_hist_entry*)list->content)->command);
			max_size = tmp;
			*pos = i;
		}
		else
			ft_fprintf(sh->debug_tty, "NO match : %s\n", ((t_ft_hist_entry*)list->content)->command);
		ft_fprintf(sh->debug_tty, "%d >= %d\n", max_size, *pos);

		if (max_size >= *pos && *pos > 0)
			break ;
		i++;
		list = (up ? list->next : list->prev);
	}
	if (*pos >= 0)
		return (((t_ft_hist_entry*)ft_lstat(sh->history, sh->history_pos +
			(up ? *pos : -1 * (*pos)))->content)->command);
	return (NULL);
}

static void print_hist(void)
{
	t_list *list;

	list = get_ft_shell()->history;
	while (list)
	{
		ft_fprintf(get_ft_shell()->debug_tty, "%s\n", ((t_ft_hist_entry*)list->content)->command);
		list = list->next;
	}
}

void	history_nav(unsigned long touch)
{
	t_ft_sh *sh;
	char	*tmp;
	int		pos;

	sh = get_ft_shell();
	print_hist();
	if (ft_strcmp(sh->buf.buf,
		((t_ft_hist_entry*)ft_lstat(sh->history, sh->history_pos)->content)->command))
		sh->history_pos = 0;
	ft_fprintf(sh->debug_tty, "Touch : %s, pos : %d\n",
	(touch == T_TARR ? "TOP" : "BOT"), sh->history_pos);
	tmp = search_in_history(sh->buf.buf, sh, (touch == T_TARR ? 1 : 0), &pos);
	if (pos >= 0)
	{
		while (sh->cursor < sh->buf.cursor)
			move_in_terminal(T_RARR, 1);
		while (sh->cursor > 0)
			backspace_command(0);
		sh->history_pos += (T_TARR ? pos : -1 * pos);
		free(sh->history_last);
		sh->history_last = ft_strdup(sh->buf.buf);
		dbuf_clear(&sh->buf);
		dbuf_append(&sh->buf, tmp);
		update_stdout(sh, 0);
		while (sh->cursor < sh->buf.cursor)
			move_in_terminal(T_RARR, 1);
	}
	ft_fprintf(sh->debug_tty, "POS : %d\n", sh->history_pos);
}
