/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_nav.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:55:43 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/08 21:19:30 by bluff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			column_offset(t_ft_sh *sh, unsigned long touch)
{
	unsigned int	i;
	unsigned int	curr;

	curr = get_sh_cursor();
	ft_fprintf(sh->debug_tty, "DEBUUUG : %s - PROMPT : %d - CURSOR : %d - SIZE : %d\n", touch == T_LARR ? "LEFT" : "RIGHT", sh->prompt_size, get_sh_cursor(), sh->x_size);
	if (touch == T_LARR && sh->is_a_tty && sh->cursor > 1 && sh->buf.buf[sh->cursor - 1] == '\n')
	{
		ft_fprintf(sh->debug_tty, "HERE 4\n");
		i = 2;
		while (sh->cursor - i - 1 > 0 && i < sh->x_size
			&& sh->buf.buf[sh->cursor - i - 1] != '\n')
			i++;
		if (sh->cursor - i - 1 == 0)
			i += sh->prompt_size + 1;
		i += (i == sh->x_size ? 2 : 0);
		return ((i % sh->x_size) - 1);
	}
	else if (touch == T_LARR && sh->is_a_tty && ((curr) % (sh->x_size - 1)) == 0)
		{
			ft_fprintf(sh->debug_tty, "HERE 1\n");
			return (sh->x_size - 1);
		}
	else if (touch == T_RARR && sh->is_a_tty &&
		((curr) % (sh->x_size)) == sh->x_size - 1)
	{
		ft_fprintf(sh->debug_tty, "HERE 2\n");
		ft_putchar('\n');
		return (1);
	}
	else if (touch == T_RARR && sh->is_a_tty && sh->buf.buf[sh->cursor] == '\n')
	{
		ft_fprintf(sh->debug_tty, "HERE 3\n");
		ft_putchar('\n');
		return (1);
	}
	return (0);
}

int			is_alt_shell_begin(void)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	return (sh->cursor > 0 && sh->buf.buf[sh->cursor - 1] == '\n' &&
		sh->is_alt_shell);
}

static void	skip_in_terminal(unsigned long touch)
{
	t_ft_sh *sh;
	int dir;
	int tmp;

	dir = ((touch == T_SLARR ? -1 : 1));
	if (touch == T_SBARR || touch == T_STARR ||
		(touch == T_SLARR && is_alt_shell_begin()))
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
	while ((touch == T_HOME && sh->cursor && !is_alt_shell_begin()) ||
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
	int offset;
	sh = get_ft_shell();
	if (touch == T_LARR && sh->cursor > 0 && !is_alt_shell_begin())
	{
		if ((offset = column_offset(sh, touch)))
		{
			ft_fprintf(sh->debug_tty, "Offset : %d\n", offset);
			exec_term_command(TC_MOVEUP);
			exec_term_command_p(TC_MOVENRIGHT, 0, offset);
		}
		else if (sh->is_a_tty)
			exec_term_command(TC_MOVELEFT);
		sh->cursor -= (should_update_buf ? 1 : 0);
	}
	else if (touch == T_RARR && sh->cursor < sh->buf.cursor)
	{
		if (!column_offset(sh, touch) && sh->is_a_tty)
			exec_term_command(TC_MOVERIGHT);
		sh->cursor += (should_update_buf ? 1 : 0);
	}
}
