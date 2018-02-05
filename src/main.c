/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:40:09 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/05 12:24:25 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <fcntl.h>

t_ft_sh	*get_ft_shell(void)
{
	static t_ft_sh shell;

	return (&shell);
}

void	init_debug(t_ft_sh *shell, const char *path)
{
	if ((shell->debug_tty = open(path, O_WRONLY)) < 0)
		return ;
	ft_fprintf(shell->debug_tty, "-------------------------------------\n");
}

int		main(int argc, const char **argv, const char **environ)
{
	t_ft_sh *shell;

	(void)environ;
	shell = get_ft_shell();
	shell->debug_tty = -1;
	dbuf_init(&shell->buf);
	if (argc == 3 && !ft_strcmp("-d", argv[1]))
		init_debug(shell, argv[2]);
	if (!is_env_correct())
		return (1);
	apply_terminal_setting(0);
	get_screen_size();
	display_prompt(0);
	char *res = read_command();
	ft_printf("\nTyped : %s\n", res);
	free(res);
	apply_terminal_setting(1);
	if (shell->debug_tty > 0)
		close(shell->debug_tty);
	return (0);
}
