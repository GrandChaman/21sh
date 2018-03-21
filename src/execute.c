/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:40:03 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/21 15:39:59 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		launch_builtin(char **cmd, t_list **head)
{
	pid_t   father;
    int     status;
	t_list	*copy;

    status = 0;
	if (ft_strcmp(cmd[0], "unsetenv") == 0)
		return (builtin_unsetenv(cmd, head));
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		return (builtin_setenv(cmd, head));
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd[1], head));
    father = fork();
    if (father > 0)
        wait(&status);
    else
    {
		if (ft_strcmp(cmd[0], "env") == 0)
		{
			copy = dup_environment(*head);
			builtin_env(&copy, cmd);
			ft_lstdel(&copy, free_env_var);
		}
		else if (ft_strcmp(cmd[0], "help") == 0)
			mini_help(cmd);
		else if (ft_strcmp(cmd[0], "echo") == 0)
			builtin_echo(cmd, head);
		exit(0);
    }
	return (status);
}

int		is_built_in(char **cmd)
{
	if (ft_strcmp(cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "help") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
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
		return (builtin_exit());
	}
	if (is_built_in(parser.cmd))
		return (launch_builtin(parser.cmd, head));
	else
		return (launch(parser.cmd, head, ht));
}
