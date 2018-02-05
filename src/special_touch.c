/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_touch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 15:28:41 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/05 13:20:53 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		spt_backspace(unsigned long touch)
{
	t_ft_sh *shell;

	(void)touch;
	shell = get_ft_shell();
	if (shell->cursor <= 0)
		return ;
	dbuf_remove(&shell->buf, --shell->cursor);
	exec_term_command(TC_MOVELEFT);
	exec_term_command(TC_DELETE);
}

void		spt_arrow(unsigned long touch)
{
	t_ft_sh *sh;

	sh = get_ft_shell();
	if (touch == T_LARR && sh->cursor > 0)
	{
		if (!((sh->prompt_size + sh->cursor) % (sh->x_size)))
		{
			exec_term_command(TC_MOVEUP);
			exec_term_command_p(TC_MOVENRIGHT, 0, sh->x_size);
		}
		else
			exec_term_command(TC_MOVELEFT);
		sh->cursor--;
	}
	else if (touch == T_RARR && sh->cursor < sh->buf.cursor)
	{
		if (!((sh->prompt_size + sh->cursor) % (sh->x_size - 1)))
		{
			exec_term_command_p(TC_MOVENLEFT, 0, sh->x_size);
			exec_term_command(TC_MOVEDOWN);
		}
		else
			exec_term_command(TC_MOVERIGHT);
		sh->cursor++;
	}
}
