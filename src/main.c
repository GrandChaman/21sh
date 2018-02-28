/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:40:09 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/28 15:24:07 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

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

void main_routine(t_list **head, int status)
{
	char *cmd;
	t_ft_sh *shell;

	shell = get_ft_shell();
	shell->is_a_tty = isatty(0);
	if (shell->is_a_tty)
	{
		apply_terminal_setting(0);
		get_screen_size();
	}
	while (status)
	{
		ft_fprintf(shell->debug_tty, "YAY\n");
		cmd = read_command(NULL, NULL);
		status = execute(&cmd, head);
		ft_fprintf(shell->debug_tty, "YAY\n");
		//ft_printf("%s%s\n", (!shell->is_a_tty ? "" : "\nTyped : "),cmd);
		free(cmd);
	}
	if (shell->is_a_tty)
		apply_terminal_setting(1);
}

int		main(int argc, const char **argv, char **env)
{
	t_ft_sh *shell;
	t_list	*head;

	shell = get_ft_shell();
	shell->debug_tty = -1;
	dbuf_init(&shell->buf);
	if (argc == 3 && !ft_strcmp("-d", argv[1]))
		init_debug(shell, argv[2]);
	if (!is_env_correct())
		return (1);
	head = create_list_from_env(env);
	main_routine(&head, 1);
	ft_lsterase(&head);
	if (shell->debug_tty > 0)
		close(shell->debug_tty);
	free(shell->select);
	return (0);
}
