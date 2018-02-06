/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:58:16 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/06 13:27:07 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		delete_and_rewrite(void)
{
	int len;
	int tmp;
	int ncursor;
	int substr_len;
	t_ft_sh *sh;

	sh = get_ft_shell();
	ncursor = sh->cursor + 1;
	len = sh->buf.cursor - sh->cursor;
	exec_term_command(TC_SAVECURPOS);
	while (len > 0)
	{
		tmp = (sh->x_size - ((sh->prompt_size + ncursor) % sh->x_size)) + 1;
		substr_len = ft_strlen((sh->buf.buf + (ncursor - 1))) + 1;
		if (tmp > substr_len)
			tmp = substr_len;
		ft_fprintf(sh->debug_tty, "Tmp : %d - \n", tmp);
		ft_printf("%*s", tmp, " ");
		exec_term_command_p(TC_MOVENLEFT, 0, tmp);
		exec_term_command_p(TC_INSERTNCHAR, 0, tmp);
		write(1, (sh->buf.buf + (ncursor - 1)), tmp);
		ft_fprintf(sh->debug_tty, "Len : %d\n", len);
		len -= tmp;
		if (len == 0)
		{
			exec_term_command_p(TC_MOVENLEFT, 0, sh->x_size - tmp);
			exec_term_command(TC_MOVEDOWN);
			ft_putchar(' ');
		}
		if (len > 0)
			ft_putchar('\n');
		ncursor += tmp;
	}
	exec_term_command(TC_RESETCURPOS);
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
		delete_and_rewrite();
}
