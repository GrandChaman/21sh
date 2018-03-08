/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:58:16 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/08 18:54:22 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		backspace_command(unsigned long touch)
{
	t_ft_sh *sh;
	int		delete_char;

	(void)touch;
	sh = get_ft_shell();
	if (sh->cursor == 0)
		return ;
	move_in_terminal(T_LARR, 1);
	delete_char = sh->buf.buf[sh->cursor];
	dbuf_remove(&sh->buf, sh->cursor);
	if (!sh->is_a_tty)
		return ;
	ft_putchar(' ');
	exec_term_command(TC_MOVELEFT);
	if (((sh->prompt_size + get_sh_cursor()) % (sh->x_size)) == sh->x_size - 1)
		exec_term_command(TC_MOVERIGHT);
	if (sh->cursor < sh->buf.cursor)
		update_stdout(sh, delete_char);
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
