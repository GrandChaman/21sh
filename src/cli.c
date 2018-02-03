/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:55:43 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/03 18:14:50 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		execute_touch(t_ft_sh *shell, unsigned long rchar)
{
	int i;

	i = -1;
	if (ft_isprint(rchar))
	{
		dbuf_insert(&shell->buf, shell->cursor++, (char)rchar);
		if (shell->cursor < shell->buf.cursor)
		{
			exec_term_command_p(TC_NDELETE, 0,
				shell->buf.cursor - shell->cursor);
			i = ft_strlen(shell->buf.buf + (shell->cursor - 1));
			exec_term_command_p("IC", 0, i);
			ft_putstr(shell->buf.buf + (shell->cursor - 1));
			exec_term_command_p("LE", 0, i - 1);

		}
		else
			ft_putchar((char)rchar);
	}
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
