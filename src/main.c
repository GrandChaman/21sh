/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:40:09 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/11 12:40:43 by bluff            ###   ########.fr       */
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
	t_parser *parser;
	int		x;
	int 	nb;

	shell = get_ft_shell();
	//load_history(shell, 0);
	while (status)
	{
		ft_fprintf(shell->debug_tty, "YAY\n");
		ft_fprintf(shell->debug_tty, "%p\n", shell->history);
		cmd = read_command(NULL, NULL, 0);
		//add_to_history(shell, cmd);
		parser = get_parser(cmd);
		nb = parser[0].nb;
		ft_putendl("");
		x = -1;
		//(void)head;
		while (++x < nb)
			status = execute(parser[x], head);
		//load_history(shell, 1);
		ft_fprintf(shell->debug_tty, "YAY\n");
		//ft_printf("%s%s\n", (!shell->is_a_tty ? "" : "\nTyped : "),cmd);
		free_parser(parser);
		free(cmd);
	}
	//load_history(shell, 1);
}

int		main(int argc, const char **argv, char **env)
{
	t_ft_sh *shell;
	t_list	*head;

	shell = get_ft_shell();
	shell->debug_tty = -1;
	if (argc == 3 && !ft_strcmp("-d", argv[1]))
		init_debug(shell, argv[2]);
	if (!is_env_correct())
		return (1);
	head = create_list_from_env(env);
	//ft_lstprint(&head);
	cli_loader(0);
	main_routine(&head, 1);
	cli_loader(1);
	ft_lsterase(&head);
	if (shell->debug_tty > 0)
		close(shell->debug_tty);
	free(shell->select);
	return (0);
}
