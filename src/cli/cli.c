/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:55:43 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/08 16:17:26 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		insert_normal_touch(t_ft_sh *sh)
{
	sh->cursor--;
	update_stdout(sh, 0);
}

static void	print_normal_touch(t_ft_sh *sh, unsigned long rchar)
{
	dbuf_insert(&sh->buf, sh->cursor++, (char)rchar);

	if (sh->cursor < sh->buf.cursor)
		insert_normal_touch(sh);
	else
	{
		ft_putchar((char)rchar);
		if (((sh->prompt_size + sh->cursor) % (sh->x_size)) == 0)
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
	int				rvalue;
	unsigned char	tmp[8];
	unsigned char	i;

	buf = &get_ft_shell()->buf;
	rchar = 0;
	rvalue = 1;
	i = 0;
	ft_bzero(tmp, 8);
	while (42)
	{
		rvalue = read(0, &tmp[i], 1);
		if (rvalue == -1 || *(tmp + i) == '\n')
			break ;
		if (tmp[0] != 27 && rvalue)
			rchar = tmp[0];
		if ((!rvalue && i) || (tmp[0] != 27 && rvalue))
		{
			rchar = *((unsigned long*)tmp);
			execute_touch(get_ft_shell(), rchar);
			ft_bzero(tmp, (i ? i : 1));
		}
		i = (rvalue && tmp[0] == 27 ? i + 1 : 0);
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
