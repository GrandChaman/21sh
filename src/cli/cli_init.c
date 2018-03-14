/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:57:06 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/14 16:23:10 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		is_env_correct(void)
{
	int res;
	t_ft_sh *sh;

	sh = get_ft_shell();
	res = tgetent(NULL, getenv("TERM"));
	if (res == -1)
		return (!ft_fprintf(2,
			"TERM environment variable is not set or is incorrect.\n"));
	else if (res == 0)
		return (!ft_fprintf(2,
			"TERM info database not found.\n"));
	return (1);
}

void	cli_reset_cursor(t_ft_sh *sh)
{
	sh->history_pos = -1;
	sh->history_last = NULL;
	sh->prompt_size = 0;
	sh->cursor = 0;
	sh->alt_cursor = 0;
	sh->is_alt_shell = 0;
}

void	cli_loader(int destroy)
{
	t_ft_sh *shell;

	shell = get_ft_shell();
	if (destroy)
	{
		load_history(shell, 1);
		if (shell->is_a_tty)
			apply_terminal_setting(destroy);
		dbuf_destroy(&shell->buf);
	}
	else
	{
		shell->history_pos = -1;
		shell->history_last = NULL;
		shell->history = NULL;
		shell->is_a_tty = isatty(0);
		if (shell->is_a_tty)
		{
			apply_terminal_setting(destroy);
			get_screen_size();
		}
		load_history(shell, 0);
		dbuf_init(&shell->buf);
	}
}
