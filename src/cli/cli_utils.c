/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:24:58 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/07 15:00:50 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		update_stdout(t_ft_sh *sh, int offset, int upt_on_scroll)
{
	int len;
	int tmp;
	int substr_len;
	int ncur;
	int ocur;

	(void)upt_on_scroll;
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
