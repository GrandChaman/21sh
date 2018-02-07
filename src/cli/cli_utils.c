/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:24:58 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/07 19:04:57 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	roll_back_cursor(t_ft_sh *sh, int ncur, int ocur)
{
	int has_print_a_nl;

	has_print_a_nl = (sh->buf.cursor + sh->prompt_size) % sh->x_size == 0;
	if (has_print_a_nl)
	{
		exec_term_command(TC_MOVEUP);
		exec_term_command_p(TC_MOVENRIGHT, 0, sh->x_size);
	}
	sh->cursor = --ncur;
	exec_term_command(TC_MOVELEFT);
	while (--ncur > ocur)
	{
		//usleep(100000);
		move_in_terminal(T_LARR, 1);
	}
	if (has_print_a_nl)
		exec_term_command(TC_MOVERIGHT);
}

void		update_stdout(t_ft_sh *sh, int isdel)
{
	int len;
	int tmp;
	int ncur;
	int ocur;

	len = (sh->buf.cursor - sh->cursor);
	ncur = sh->cursor + isdel;
	ocur = ncur;
	while (len > 0)
	{
		tmp = ((sh->x_size) - ((sh->prompt_size + ncur) % sh->x_size)) + isdel;
		if (tmp > len + isdel)
			tmp = len + isdel;
		ft_printf("%*s", tmp, " ");
		exec_term_command_p(TC_MOVENLEFT, 0, tmp);
		ft_fprintf(sh->debug_tty, "BCURSOR : %d NCUR : %d LEN : %d TMP : %d\n", sh->buf.cursor, ncur, len, tmp);
		exec_term_command_p(TC_INSERTNCHAR, 0, tmp);
		write(1, (sh->buf.buf + ncur - isdel), tmp);
		len -= tmp;
		ncur += tmp;
		if ((isdel && len >= 0) || (!isdel && (len > 0
			|| (sh->buf.cursor + sh->prompt_size) % sh->x_size == 0)))
			ft_putchar('\n');
	}
	if (!isdel)
		roll_back_cursor(sh, ncur, ocur);
}

void update_stdout_insert(t_ft_sh *sh, int offset)
{
	int len;
	int tmp;
	int substr_len;
	int ncur;
	int ocur;

	len = sh->buf.cursor - sh->cursor;
	ncur = sh->cursor + offset;
	ocur = ncur;
	substr_len = ft_strlen((sh->buf.buf + (ncur)));
	while (len > 0)
	{
		tmp = ((sh->x_size) - ((sh->prompt_size + ncur) % sh->x_size)) + offset;
		ft_fprintf(sh->debug_tty, "SUB VS TMP : %d | %d \n", substr_len, tmp);
		if (tmp > substr_len)
			tmp = substr_len;
		usleep(500000);
		ft_printf("%*s", tmp, " ");
		usleep(500000);
		exec_term_command_p(TC_MOVENLEFT, 0, tmp);
		exec_term_command_p(TC_INSERTNCHAR, 0, tmp);
		write(1, (sh->buf.buf + ncur - offset), tmp);
		len -= tmp;
		ncur += tmp;
		ft_fprintf(sh->debug_tty, "DEBUG : %d | %d | %d\n", len, sh->buf.cursor + sh->prompt_size, ((sh->buf.cursor + sh->prompt_size) % sh->x_size));
		if (len > 0 || (len == 0 && ((sh->buf.cursor + sh->prompt_size) % sh->x_size) == 0))
			ft_putchar('\n');
		substr_len -= tmp;
	}
	sh->cursor = ncur;
	while (ncur-- > ocur)
	{
		move_in_terminal(T_LARR, 1);
		usleep(100000);
	}
}
