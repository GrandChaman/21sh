/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_touch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 15:28:41 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/03 18:53:42 by fle-roy          ###   ########.fr       */
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
	t_ft_sh *shell;

	shell = get_ft_shell();
	if (touch == T_LARR && shell->cursor > 0)
	{
		exec_term_command(TC_MOVELEFT);
		shell->cursor--;
	}
	else if (touch == T_RARR && shell->cursor < shell->buf.cursor)
	{
		exec_term_command(TC_MOVERIGHT);
		shell->cursor++;
	}
}
