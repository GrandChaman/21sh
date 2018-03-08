/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:24:58 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/08 18:49:31 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static unsigned int			cursor_new_origin(t_ft_sh *sh)
{
	unsigned int i;
	unsigned int res;

	res = 0;
	i = 0;
	while ((int)(sh->cursor - i) > 0)
	{
		if (sh->buf.buf[sh->cursor - i] == '\n')
		{
			res = sh->cursor - (sh->cursor - i + sh->prompt_size) - 1;
			break ;
		}
		i++;
	}
	res = (i < sh->x_size ? res + sh->x_size : res);
	return (res);
}

unsigned int get_sh_cursor(void)
{
	t_ft_sh *sh;
	unsigned int norig_cur;

	sh = get_ft_shell();
	norig_cur = cursor_new_origin(sh);
	if (norig_cur < sh->cursor)
		return (norig_cur - sh->alt_cursor);
	return (sh->cursor - sh->alt_cursor);
}

void		update_stdout(t_ft_sh *sh, int isdel)
{
	unsigned int save_cur;

	save_cur = sh->cursor;
	(void)isdel;
	while (sh->cursor)
		move_in_terminal(T_LARR, 1);
	exec_term_command(TC_CLEAR_LINE);
	if ((sh->buf.cursor + sh->prompt_size - isdel) >= sh->x_size || isdel == '\n' ||
		ft_strchr(sh->buf.buf, '\n'))
	{
		exec_term_command(TC_MOVEDOWN);
		exec_term_command(TC_CARRIAGERETURN);
		exec_term_command(TC_CLEAR_BELOW);
		exec_term_command(TC_MOVEUP);
		exec_term_command_p(TC_MOVENRIGHT, 0, sh->prompt_size);
	}
	write(1, sh->buf.buf, sh->buf.cursor);
	sh->cursor = sh->buf.cursor - !isdel;
	if (((sh->prompt_size + sh->cursor) % (sh->x_size)) == 0)
		ft_putchar('\n');
	while (sh->cursor != save_cur + !isdel)
		move_in_terminal(T_LARR, 1);
}

void		(*get_special_char_f(unsigned long val))(unsigned long)
{
	int i;

	i = -1;
	while (g_ft_touch_list[++i].touch)
		if (g_ft_touch_list[i].touch == val)
			return (g_ft_touch_list[i].f);
	return (NULL);
}
