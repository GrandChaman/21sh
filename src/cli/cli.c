/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:55:43 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/11 11:42:58 by bluff            ###   ########.fr       */
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
			if (((sh->prompt_size + get_sh_cursor()) % (sh->x_size)) == 0)
				ft_putchar('\n');
		}
}

void		execute_touch(t_ft_sh *shell, unsigned long rchar)
{
	int		i;
	int		cur_save;
	void	(*f)(unsigned long);

	i = shell->cursor + 1;
	if (rchar == T_CTRL_C)
		exit(0);
	if (rchar != T_ALT_C && rchar != T_ALT_V && rchar != T_ALT_X &&
		rchar != T_ALT_LEFT && rchar != T_ALT_RIGHT && shell->select_size)
	{
		exec_term_command(TC_SAVECURPOS);
		cur_save = shell->cursor;
		while (i-- > 0)
			move_in_terminal(T_LARR, 1);
		update_stdout(shell, 0);
		shell->select_start = 0;
		shell->select_size = 0;
		exec_term_command(TC_RESETCURPOS);
		shell->cursor = cur_save;
	}
	if (ft_isprint(rchar))
		print_normal_touch(shell, rchar);
	else
		if ((f = get_special_char_f(rchar)))
			f(rchar);
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
	return (res);
}

void		read_command_routine(void)
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
		ft_fprintf(get_ft_shell()->debug_tty, "TMP : %d\n", tmp[0]);
		if (rvalue == -1 || tmp[0] == '\n' || tmp[0] == T_CTRL_D || tmp[0] == T_CTRL_C)
			break ;
		rchar = *((unsigned long*)tmp);
		if (get_special_char_f(rchar) || ft_isprint(rchar) || (tmp[0] != 0 && !rvalue))
		{
			ft_fprintf(get_ft_shell()->debug_tty, "Cursor : %d - rchar : %U\n", get_sh_cursor(), *((unsigned long*)tmp));
			execute_touch(get_ft_shell(), rchar);
			ft_bzero(tmp, 8);
			i = 0;
			continue ;
		}
		if (i == 7 && rvalue)
			ft_bzero(tmp, 8);
		i = (rvalue && i < 7 ? i + 1 : 0);
	}
}

char		*read_command(char *prompt, int *status, int heredoc)
{
	char *nprompt;
	t_ft_sh *sh;
	char *res;

	sh = get_ft_shell();
	if (prompt || heredoc)
	{
		prompt = (prompt ? prompt : "heredoc> ");
		ft_printf(prompt);
		get_ft_shell()->prompt_size = ft_strlen(prompt);
	}
	else
		display_prompt((status ? *status : 1));
	sh->is_alt_shell = (prompt || heredoc ? 1 : 0);
	read_command_routine();
	if (!heredoc && (nprompt = check_correct(get_ft_shell()->buf.buf)))
	{
		sh->cursor = sh->buf.cursor;
		sh->alt_cursor = sh->cursor + 1;
		dbuf_insert(&sh->buf, sh->cursor++, '\n');
		ft_putchar('\n');
		return (read_command(nprompt, status, 0));
	}
	res = ft_strdup(get_ft_shell()->buf.buf);
	sh->cursor = 0;
	sh->alt_cursor = 0;
	ft_free((void**)&sh->history_last);
	dbuf_clear(&sh->buf);
	return (res);
}
