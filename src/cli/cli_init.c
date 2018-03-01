/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:57:06 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/01 13:14:19 by fle-roy          ###   ########.fr       */
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

void	cli_loader(int destroy)
{
	t_ft_sh *shell;

	shell = get_ft_shell();
	if (destroy)
	{
		if (shell->is_a_tty)
			apply_terminal_setting(destroy);
		dbuf_destroy(&shell->buf);
	}
	else
	{
		shell->is_a_tty = isatty(0);
		if (shell->is_a_tty)
		{
			apply_terminal_setting(destroy);
			get_screen_size();
		}
		dbuf_init(&shell->buf);
	}
}
