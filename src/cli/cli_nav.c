/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_nav.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:55:43 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/01 16:37:23 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			is_a_new_line(void)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	return (sh->buf.buf[sh->cursor - 1] == '\n');
}

static void	skip_in_terminal(unsigned long touch)
{
	t_ft_sh *sh;
	int dir;
	int tmp;

	dir = ((touch == T_SLARR ? -1 : 1));
	if (touch == T_SBARR || touch == T_STARR ||
		(touch == T_SLARR && is_a_new_line()))
		return ;
	sh = get_ft_shell();
	while (sh->cursor + (dir > 0) > 0
		&& (int)sh->cursor < sh->buf.cursor + (dir < 0))
	{
		move_in_terminal((dir < 0 ? T_LARR : T_RARR), 1);
		tmp = ((int)(sh->cursor - 1) < 0 ? 0 : sh->cursor - 1);
		if (ft_iswhitespace(sh->buf.buf[tmp]) &&
			!ft_iswhitespace(sh->buf.buf[sh->cursor]))
			break ;
	}
}

static void	home_or_end_touch(unsigned long touch)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	while ((touch == T_HOME && sh->cursor && !is_a_new_line()) ||
		(touch == T_END && sh->cursor < sh->buf.cursor))
		move_in_terminal((touch == T_HOME ? T_LARR : T_RARR), 1);
}

void		nav_touch_received(unsigned long touch)
{
	if ((touch & SHIFT_MASK) == SHIFT_MASK)
		skip_in_terminal(touch);
	else if (touch == T_HOME || touch == T_END)
		home_or_end_touch(touch);
	else
		move_in_terminal(touch, 1);
}

void		move_in_terminal(unsigned long touch, int should_update_buf)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	if (touch == T_LARR && sh->cursor > 0 && !is_a_new_line())
	{
		if (sh->is_a_tty && ((sh->prompt_size + sh->cursor) % (sh->x_size)) == 0)
		{
			exec_term_command(TC_MOVEUP);
			exec_term_command_p(TC_MOVENRIGHT, 0, sh->x_size - 1);
		}
		else if (sh->is_a_tty)
			exec_term_command(TC_MOVELEFT);
		sh->cursor -= (should_update_buf ? 1 : 0);
	}
	else if (touch == T_RARR && sh->cursor < sh->buf.cursor)
	{
		if (sh->is_a_tty && ((sh->prompt_size + sh->cursor) % (sh->x_size)) == sh->x_size - 1)
		{
			exec_term_command_p(TC_MOVENLEFT, 0, sh->x_size - 1);
			exec_term_command(TC_MOVEDOWN);
		}
		else if (sh->is_a_tty)
			exec_term_command(TC_MOVERIGHT);
		sh->cursor += (should_update_buf ? 1 : 0);
	}
}
