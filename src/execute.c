/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:40:03 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/20 17:40:55 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		launch_built_in(t_parser parser, t_list **head)
{
	pid_t   father;
    int     osef;

    osef = 0;
    father = fork();
    if (father > 0)
        wait(&osef);
    else
    {
		if (ft_strcmp(parser.cmd[0], "help") == 0)
			mini_help(parser.cmd);
		else if (ft_strcmp(parser.cmd[0], "echo") == 0)
			mini_echo(parser.cmd, head);
		exit(0);
    }
	return (-1);
}

int		is_built_in(t_parser parser)
{
	if (ft_strcmp(parser.cmd[0], "help") == 0)
		return (1);
	else if (ft_strcmp(parser.cmd[0], "echo") == 0)
		return (1);
	return (0);
}

int		execute(t_parser parser, t_list **head, int *should_exit, t_bin_hash_table *ht)
{
	t_list	*copy;

	if (!parser.cmd[0])
		return (1);
	if (ft_strcmp(parser.cmd[0], "exit") == 0)
	{
		*should_exit = 1;
		return (mini_exit(parser.cmd));
	}
	if (is_built_in(parser))
	{
		launch_built_in(parser, head);
		return (0);
	}
	if (ft_strcmp(parser.cmd[0], "cd") == 0)
		change_dir(head, (parser.cmd + 1 && *(parser.cmd + 1))
			? *(parser.cmd + 1) : NULL);
	else if (ft_strcmp(parser.cmd[0], "unsetenv") == 0)
		mini_unsetenv(parser.cmd, head);
	else if (ft_strcmp(parser.cmd[0], "setenv") == 0)
		mini_setenv(parser.cmd, head);
	if (ft_strcmp(parser.cmd[0], "env") == 0)
	{
		copy = dup_environment(*head);
		builtin_env(&copy, parser.cmd, ht);
		ft_lstdel(&copy, free_env_var);
		return (0);
	}
	return (launch(parser.cmd, head, ht));
}
