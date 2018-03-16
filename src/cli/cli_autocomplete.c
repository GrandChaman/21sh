/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:26:13 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/16 16:21:44 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		delete_autocomplete_entry(void *el, size_t size)
{
	(void)size;
	ft_free((void**)&((t_ft_autoc_entry*)el)->name);
}

static void		ready_cursor_autocompletion()
{
	unsigned int	cur_save;
	t_ft_sh *sh;

	sh = get_ft_shell();
	cur_save = sh->cursor;
	exec_term_command(TC_SAVECURPOS);
	while (sh->cursor < sh->buf.cursor)
		move_in_terminal(T_RARR, 1);
	ft_putchar('\n');
	sh->cursor = cur_save;
}

void			cancel_autocompletion(t_ft_sh *shell, unsigned long rchar)
{
	if (shell->autocomplete && rchar != T_TAB && rchar != T_LARR &&
		rchar != T_RARR && rchar != T_BARR && rchar != T_TARR
		&& rchar != T_ENTER)
	{
		ready_cursor_autocompletion();
		exec_term_command(TC_CLEAR_FROM_HERE);
		exec_term_command(TC_RESETCURPOS);
		if (shell->autocomplete)
			ft_lstdel(&shell->autocomplete, delete_autocomplete_entry);
		shell->autocomplete_cusor = NULL;
	}
}

static void		select_autocompletion(t_ft_autoc_entry *item, int invert_video)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	if (invert_video)
		exec_term_command(TC_REVERSEVIDEO);
	if (item->y_pos > 0)
		exec_term_command_p(TC_MOVENDOWN, 0, item->y_pos);
	if (item->x_pos > 0)
		exec_term_command_p(TC_MOVENRIGHT, 0, item->x_pos);
	ft_printf("%s%-*s{eoc}", item->color, sh->autocomplete_padding, item->name);
	if (invert_video)
	{
		exec_term_command(TC_RESETGRAPHICS);
		exec_term_command(TC_RESETCURPOS);
	}
	else
	{
		if (item->y_pos > 0)
			exec_term_command_p(TC_MOVENUP, 0, item->y_pos);
		exec_term_command_p(TC_MOVENLEFT, 0, item->x_pos +
			sh->autocomplete_padding);
	}
}

void			move_in_autocompletion(unsigned long touch)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	ready_cursor_autocompletion();
	if (touch == T_TAB)
		touch = T_RARR;
	if (sh->autocomplete_cusor)
		select_autocompletion(sh->autocomplete_cusor->content, 0);
	if (!sh->autocomplete_cusor)
		sh->autocomplete_cusor = sh->autocomplete;
	else if (sh->autocomplete_cusor && (touch == T_LARR || touch == T_RARR))
	{
		if (touch == T_LARR && !sh->autocomplete_cusor->prev)
			while (sh->autocomplete_cusor->next)
				sh->autocomplete_cusor = sh->autocomplete_cusor->next;
		else if (touch == T_RARR && !sh->autocomplete_cusor->next)
			while (sh->autocomplete_cusor->prev)
				sh->autocomplete_cusor = sh->autocomplete_cusor->prev;
		else if (touch == T_LARR)
			sh->autocomplete_cusor = sh->autocomplete_cusor->prev;
		else if (touch == T_RARR)
			sh->autocomplete_cusor = sh->autocomplete_cusor->next;
	}
	select_autocompletion(sh->autocomplete_cusor->content, 1);
}

static void		display_autocomplete(t_ft_sh *sh, t_list *list)
{
	t_ft_autoc_entry*	tmp;
	int					last_y;

	ready_cursor_autocompletion();
	last_y = 0;
	while (list)
	{
		tmp = ((t_ft_autoc_entry*)list->content);
		if (tmp->y_pos != last_y)
		{
			exec_term_command(TC_CARRIAGERETURN);
			if (last_y < tmp->y_pos)
				exec_term_command(TC_MOVEDOWN);
			else
				exec_term_command_p(TC_MOVENUP, 0, last_y - tmp->y_pos);
			last_y = tmp->y_pos;
		}
		ft_printf("%s%-*s{eoc}", tmp->color, sh->autocomplete_padding,
			tmp->name);
		list = list->next;
	}
	exec_term_command(TC_RESETCURPOS);
}

void		ft_sh_autocomplete(unsigned long touch)
{
	int i;
	char *str_part;
	t_ft_sh *sh;

	sh = get_ft_shell();
	i = 0;
	if (!sh->autocomplete && touch == T_TAB)
	{
		while (sh->cursor - i > 0 && ft_iswhitespace(sh->buf.buf[sh->cursor - i]))
			i++;
		str_part = (!i ? NULL : ft_strndup(sh->buf.buf + sh->cursor - i, i));
		collect_data(str_part);
		display_autocomplete(sh, sh->autocomplete);
		free(str_part);
	}
	else if (sh->autocomplete &&
		(touch == T_TAB || touch == T_LARR || touch == T_RARR ||
			touch == T_BARR || touch == T_TARR))
		move_in_autocompletion(touch);
}
