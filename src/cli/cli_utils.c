/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:24:58 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/07 17:49:36 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	roll_back_cursor(t_ft_sh *sh, int ncur, int ocur)
{
	sh->cursor = --ncur;
	exec_term_command(TC_MOVELEFT);
	while (ncur-- > ocur + 100)
	{
		usleep(100000);
		move_in_terminal(T_LARR, 1);
	}
}

void		update_stdout(t_ft_sh *sh, int isdelsert)
{
	int len;
	int tmp;
	int ncur;
	int ocur;

	len = (sh->buf.cursor - sh->cursor);
	ncur = sh->cursor + (isdelsert ? 1 : 0);
	ocur = ncur;
	while (len > 0)
	{
		tmp = ((sh->x_size) - ((sh->prompt_size + ncur) % sh->x_size)) + isdelsert;
		if (tmp > len + 1)
			tmp = len + 1;
		ft_printf("%*s", tmp, " ");
		exec_term_command_p(TC_MOVENLEFT, 0, tmp);
		ft_fprintf(sh->debug_tty, "LEN : %d TMP : %d\n", len, tmp);
		exec_term_command_p(TC_INSERTNCHAR, 0, tmp);
		write(1, (sh->buf.buf + ncur - isdelsert), tmp);
		len -= tmp;
		ncur += tmp;
		if (len >= 0)
			ft_putchar('\n');
	}
	if (!isdelsert)
		roll_back_cursor(sh, ncur, ocur);
}
