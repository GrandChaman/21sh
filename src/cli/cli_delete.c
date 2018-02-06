/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:58:16 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/06 17:05:31 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		delete_and_rewrite(t_ft_sh *sh)
{
	update_stdout(sh, --sh->cursor, 0);
}

void		backspace_command(unsigned long touch)
{
	t_ft_sh *sh;

	(void)touch;
	sh = get_ft_shell();
	if (sh->cursor <= 0)
		return ;
	dbuf_remove(&sh->buf, sh->cursor - 1);
	move_in_terminal(T_LARR, 1);
	ft_putchar(' ');
	exec_term_command(TC_MOVELEFT);
	if (((sh->prompt_size + sh->cursor) % (sh->x_size)) == sh->x_size - 1)
		exec_term_command(TC_MOVERIGHT);
	if (sh->cursor < sh->buf.cursor)
		update_stdout(sh, sh->cursor, 1);
}

void		delete_command(unsigned long touch)
{
	t_ft_sh *sh;

	(void)touch;
	sh = get_ft_shell();
	if (sh->cursor <= 0)
		return ;
	dbuf_remove(&sh->buf, sh->cursor);
	if (sh->cursor == sh->buf.cursor)
	{
		ft_putchar(' ');
		exec_term_command(TC_MOVENLEFT);
	}
	else if (sh->cursor < sh->buf.cursor)
		update_stdout(sh, sh->cursor, 1);
}
