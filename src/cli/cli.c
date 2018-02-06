/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:55:43 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/06 11:22:29 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		insert_normal_touch(t_ft_sh *sh)
{
	int len;
	int tmp;
	int ncursor;
	int substr_len;

	ncursor = sh->cursor - 1;
	len = sh->buf.cursor - sh->cursor;
	exec_term_command(TC_SAVECURPOS);
	while (len > 0)
	{
		tmp = sh->x_size - ((sh->prompt_size + ncursor) % sh->x_size);
		substr_len = ft_strlen((sh->buf.buf + (ncursor - 1)));
		if (tmp > substr_len)
			tmp = substr_len;
		exec_term_command_p(TC_NDELETE, 0, tmp);
		exec_term_command_p(TC_INSERTNCHAR, 0, tmp);
		write(1, (sh->buf.buf + (ncursor - 1)), tmp);
		len -= tmp;
		if (len > 0)
			exec_term_command(TC_GOTONEXTLINE);
		ncursor += tmp;
	}
	exec_term_command(TC_RESETCURPOS);
	spt_arrow(T_RARR);
}

static void	print_normal_touch(t_ft_sh *sh, unsigned long rchar)
{
	dbuf_insert(&sh->buf, sh->cursor++, (char)rchar);

	if (sh->cursor < sh->buf.cursor)
		insert_normal_touch(sh);
	else
		ft_putchar((char)rchar);
	ft_fprintf(sh->debug_tty, "INSERTING : Prompt : %d, Cursor : %d, Size : %d, Result : %d\n", sh->prompt_size, sh->cursor, sh->x_size, (sh->prompt_size + sh->cursor) % (sh->x_size));
	if (((sh->prompt_size + sh->cursor) % (sh->x_size)) == 0)
	{
		ft_fprintf(sh->debug_tty, "Going next line\n");
		ft_putchar('\n');
	}
}

void		execute_touch(t_ft_sh *shell, unsigned long rchar)
{
	int i;

	i = -1;
	if (ft_isprint(rchar))
		print_normal_touch(shell, rchar);
	else
		while (++i < 14)
			if (g_ft_touch_list[i].touch == rchar)
			{
				g_ft_touch_list[i].f(rchar);
				break;
			}
}

char		*read_command(void)
{
	t_dbuf			*buf;
	unsigned long	rchar;

	buf = &get_ft_shell()->buf;
	rchar = 0;
	while (rchar != '\n')
	{
		rchar = 0;
		read(0, &rchar, 8);
		execute_touch(get_ft_shell(), rchar);
	}
	return (buf->buf);
}

int		display_prompt(int last_result)
{
	char		*path;
	int			res;
	t_ft_sh	*shell;

	res = 4;
	if ((path = ft_getcwd()))
		res += ft_strlen(path);
	else
		res += ft_strlen("(null)");
	ft_printf("%s$ {cyan}%s{eoc}> ",
	(last_result ? ANSI_COLOR_B_RED : ANSI_COLOR_B_GREEN), path);
	free(path);
	shell = get_ft_shell();
	shell->prompt_size = res;
	dbuf_clear(&shell->buf);
	shell->cursor = 0;
	return (res);
}
