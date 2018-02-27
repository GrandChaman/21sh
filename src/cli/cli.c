/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:55:43 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/27 17:13:00 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		insert_normal_touch(t_ft_sh *sh)
{
	if (!sh->is_a_tty)
		return ;
	sh->cursor--;
	update_stdout(sh, 0);
}

static void	print_normal_touch(t_ft_sh *sh, unsigned long rchar)
{
	dbuf_insert(&sh->buf, sh->cursor++, (char)rchar);

	if (sh->cursor < sh->buf.cursor)
		insert_normal_touch(sh);
	else
		if (sh->is_a_tty)
		{
			ft_putchar((char)rchar);
			if (((sh->prompt_size + sh->cursor) % (sh->x_size)) == 0)
				ft_putchar('\n');
		}
}

void		execute_touch(t_ft_sh *shell, unsigned long rchar)
{
	int		i;
	void	(*f)(unsigned long);

	i = shell->cursor;
	if (rchar != T_ALT_C && rchar != T_ALT_V && rchar != T_ALT_X &&
		rchar != T_ALT_LEFT && rchar != T_ALT_RIGHT && shell->select_size)
	{
		exec_term_command(TC_SAVECURPOS);
		while (i--)
			move_in_terminal(T_LARR, 0);
		i = shell->cursor;
		shell->cursor = 0;
		update_stdout(shell, 0);
		shell->select_start = 0;
		shell->select_size = 0;
		exec_term_command(TC_RESETCURPOS);
		shell->cursor = i;
	}
	if (ft_isprint(rchar))
		print_normal_touch(shell, rchar);
	else
		if ((f = get_special_char_f(rchar)))
			f(rchar);
}

char		*read_command(void)
{
	unsigned long	rchar;
	int				rvalue;
	unsigned char	tmp[8];
	unsigned char	i;

	rchar = 0;
	rvalue = 1;
	i = 0;
	ft_bzero(tmp, 8);
	while (42)
	{
		rvalue = read(0, &tmp[i], 1);
		if (rvalue == -1 || tmp[0] == '\n')
			break ;
		rchar = *((unsigned long*)tmp);
		if ((tmp[0] == 27 && get_special_char_f(rchar)) || (tmp[0] != 0 && !rvalue))
		{
			ft_fprintf(get_ft_shell()->debug_tty, "rchar : %U\n", *((unsigned long*)tmp));
			execute_touch(get_ft_shell(), rchar);
			ft_bzero(tmp, 8);
			i = 0;
		}
		i = (rvalue && i < 7 ? i + 1 : 0);
	}
	return (get_ft_shell()->buf.buf);
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
