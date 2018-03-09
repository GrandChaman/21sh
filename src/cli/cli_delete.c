/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:58:16 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/07 12:18:49 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		backspace_command(unsigned long touch)
{
	t_ft_sh *sh;

	(void)touch;
	sh = get_ft_shell();
	if (get_sh_cursor() <= 0)
		return ;
	move_in_terminal(T_LARR, 1);
	dbuf_remove(&sh->buf, sh->cursor);
	if (!sh->is_a_tty)
		return ;
	ft_putchar(' ');
	exec_term_command(TC_MOVELEFT);
	if (((sh->prompt_size + get_sh_cursor()) % (sh->x_size)) == sh->x_size - 1)
		exec_term_command(TC_MOVERIGHT);
	if (sh->cursor < sh->buf.cursor)
		update_stdout(sh, 1);
}

void		delete_command(unsigned long touch)
{
	t_ft_sh *sh;

	(void)touch;
	sh = get_ft_shell();
	if (sh->cursor == sh->buf.cursor)
		return ;
	move_in_terminal(T_RARR, 1);
	backspace_command(T_BACKSPACE);
}
