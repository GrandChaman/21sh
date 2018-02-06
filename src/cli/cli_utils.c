/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:24:58 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/06 17:43:24 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		update_stdout(t_ft_sh *sh, int offset, int upt_on_scroll)
{
	int len;
	int tmp;
	int substr_len;
	int ncur;

	len = sh->buf.cursor - sh->cursor;
	ncur = sh->cursor + offset;
	exec_term_command(TC_SAVECURPOS);
	while (len > 0)
	{
		tmp = (sh->x_size - ((sh->prompt_size + ncur) % sh->x_size)) + offset;
		substr_len = ft_strlen((sh->buf.buf + (ncur - offset))) + offset;
		if (tmp > substr_len)
			tmp = substr_len;
		ft_printf("%*s", tmp, " ");
		ft_fprintf(sh->debug_tty, "TMP : %d LEN : %d\n", tmp, len);
		sleep(1);
		exec_term_command_p(TC_MOVENLEFT, 0, tmp);
		sleep(1);

		exec_term_command_p(TC_INSERTNCHAR, 0, tmp);
		sleep(1);
		write(1, (sh->buf.buf + ncur - offset), tmp);
		sleep(1);
		len -= tmp;
		if (len > 0)
			ft_putchar('\n');
		ncur += tmp;
	}
	exec_term_command(TC_RESETCURPOS);
	ft_fprintf(sh->debug_tty, "DEBUG : %d\n", (sh->prompt_size + sh->buf.cursor) % sh->x_size);
	if (upt_on_scroll && (sh->prompt_size + sh->buf.cursor) % sh->x_size == 1)
		exec_term_command(TC_MOVEUP);
}
