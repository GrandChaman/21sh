/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_nav.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:55:43 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/08 17:03:34 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		move_in_terminal(unsigned int touch, int should_update_buf)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	if (touch == T_LARR && sh->cursor > 0)
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
