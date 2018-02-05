/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_touch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 15:28:41 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/05 18:08:49 by fle-roy          ###   ########.fr       */
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
		tmp = sh->x_size - ((sh->prompt_size + ncursor) % sh->x_size - 1);
		substr_len = ft_strlen((sh->buf.buf + (ncursor - 1)));
		if (tmp > substr_len)
			tmp = substr_len + 1;
		exec_term_command_p(TC_NDELETE, 0, tmp + 1);
		exec_term_command_p(TC_INSERTNCHAR, 0, tmp);
		write(1, (sh->buf.buf + (ncursor - 1)), tmp);
		ft_fprintf(sh->debug_tty, "Len 1 : %d\n", len);
		len -= tmp;
		ft_fprintf(sh->debug_tty, "Len 2 : %d\n", len);
		if (len > 0)
			ft_putchar('\n');
		ncursor += tmp;
	}
	exec_term_command(TC_RESETCURPOS);
}

void		spt_backspace(unsigned long touch)
{
	t_ft_sh *sh;
	char save;

	(void)touch;
	sh = get_ft_shell();
	if (sh->cursor <= 0)
		return ;
	dbuf_remove(&sh->buf, sh->cursor - 1);
	if (!((sh->prompt_size + sh->cursor) % (sh->x_size - 1)))
	{
		save = sh->buf.buf[sh->cursor - 1];
		ft_fprintf(sh->debug_tty, "Save : %c\n", save);
		exec_term_command(TC_MOVELEFT);
		exec_term_command_p(TC_NDELETE, 0, 2);
		ft_putchar(save);
	}
	else
		backspace_command();
	if (sh->cursor < sh->buf.cursor)
		delete_and_rewrite();
}

void		spt_delete(unsigned long touch)
{
	t_ft_sh *shell;

	(void)touch;
	shell = get_ft_shell();
	if (shell->cursor <= 0)
		return ;
	dbuf_remove(&shell->buf, shell->cursor);
	exec_term_command(TC_DELETE);
}

void		spt_arrow(unsigned long touch)
{
	move_in_terminal(touch, 1);
}
