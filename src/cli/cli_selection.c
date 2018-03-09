/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_selection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 11:18:55 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/09 13:48:17 by bluff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		move_select(unsigned long touch)
{
	t_ft_sh *sh;
	int		tmp;

	sh = get_ft_shell();
	if (((sh->cursor == 0 || is_alt_shell_begin()) && touch == T_ALT_LEFT)
		|| (sh->cursor == sh->buf.cursor && touch == T_ALT_RIGHT))
		return ;
	if (!sh->select_size)
		sh->select_start = sh->cursor;
	tmp = sh->select_size + (touch == T_ALT_LEFT ? -1 : 1);
	if (sh->select_start + tmp - 1 != sh->cursor)
		move_in_terminal((touch == T_ALT_LEFT ? T_LARR : T_RARR), 1);
	if (ABS(tmp) > ABS(sh->select_size))
		exec_term_command(TC_REVERSEVIDEO);
	ft_putchar(sh->buf.buf[sh->cursor]);
	if (sh->cursor == 0 || is_alt_shell_begin())
		exec_term_command(TC_MOVELEFT);
	else
		move_in_terminal(T_LARR, 0);
	 if (sh->select_start + tmp - 1 == sh->cursor)
	 	move_in_terminal(T_RARR, 1);
	exec_term_command(TC_RESETGRAPHICS);
	sh->select_size += (touch == T_ALT_LEFT ? -1 : 1);
}

void		copy_select(unsigned long touch)
{
	t_ft_sh	*sh;

	(void)touch;
	sh = get_ft_shell();
	free(sh->select);
	if (sh->select_size < 0)
		sh->select = ft_strsub(sh->buf.buf, sh->select_start + sh->select_size,
			sh->select_size * -1);
	else
		sh->select = ft_strsub(sh->buf.buf, sh->select_start, sh->select_size);
	ft_fprintf(sh->debug_tty, "Copy is : %d %s\n", sh->select_start + sh->select_size, sh->select);
}

void		paste_select(unsigned long touch)
{
	t_ft_sh	*sh;
	int		i;
	int		len;

	(void)touch;
	sh = get_ft_shell();
	len = ft_strlen(sh->select);
	i = 0;
	while (i < len)
	{
		dbuf_insert(&sh->buf, sh->cursor + i, sh->select[i]);
		i++;
	}
	update_stdout(sh, 0);
	while (--i > 0)
		move_in_terminal(T_RARR, 1);
	ft_fprintf(sh->debug_tty, "Paste is : %s\n", sh->select);
}

void		cut_select(unsigned long touch)
{
	t_ft_sh	*sh;
	int		len;
	int		tmp;

	(void)touch;
	sh = get_ft_shell();
	free(sh->select);
	if (sh->select_size < 0)
		sh->select = ft_strsub(sh->buf.buf, sh->select_start + sh->select_size,
			sh->select_size * -1);
	else
		sh->select = ft_strsub(sh->buf.buf, sh->select_start, sh->select_size);
	len = ft_strlen(sh->select);
	tmp = len;
	while (len-- > 0)
		if (sh->cursor == sh->buf.cursor)
			backspace_command(T_BACKSPACE);
		else
			delete_command(T_DELETE);
	sh->select_start = 0;
	sh->select_size = 0;
	ft_fprintf(sh->debug_tty, "Cut is : %d %s\n",
		sh->select_start + sh->select_size, sh->select);
}
