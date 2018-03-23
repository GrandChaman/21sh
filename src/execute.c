/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:40:03 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/23 15:23:26 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	launch_forked_builtin(char **cmd, t_list **head, t_parser parser,
	t_dup *dup_el)
{
	t_list *copy;

	open_fds_in_fork(&parser, dup_el);
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		copy = dup_environment(*head);
		builtin_env(&copy, cmd, parser);
		ft_lstdel(&copy, free_env_var);
	}
	else if (ft_strcmp(cmd[0], "help") == 0)
		mini_help(cmd);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		builtin_echo(cmd, head);
	exit(0);
}

int			launch_builtin(char **cmd, t_list **head, t_parser parser,
	t_wait_el *el)
{
	if (ft_strcmp(cmd[0], "unsetenv") == 0)
		return (builtin_unsetenv(cmd, head));
	else if (ft_strcmp(cmd[0], "setenv") == 0)
		return (builtin_setenv(cmd, head));
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (builtin_cd(cmd[1], head));
	else if (ft_strcmp(cmd[0], "hash") == 0)
		return (gen_hash(*head));
	init_pipe_in_parent(&parser, get_dup_el());
	el->pid = fork();
	if (!el->pid)
		launch_forked_builtin(cmd, head, parser, get_dup_el());
	else if (el->pid < 0)
		ft_putendl("21sh: fork error\n");
	close_fds_in_parent(&parser, get_dup_el());
	return (0);
}

int			is_built_in(char **cmd)
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
	else if (ft_strcmp(cmd[0], "hash") == 0)
		return (1);
	return (0);
}

t_wait_el	execute(t_parser parser, t_list **head, int *should_exit,
	t_bin_hash_table *ht)
{
	t_wait_el el;

	el.pid = -1;
	el.is_piped = parser.output.pipe;
	if (!parser.cmd || !parser.cmd[0])
		return (el);
	if (ft_strcmp(parser.cmd[0], "exit") == 0)
	{
		*should_exit = 1;
		builtin_exit();
		return (el);
	}
	if (is_built_in(parser.cmd))
	{
		launch_builtin(parser.cmd, head, parser, &el);
		return (el);
	}
	else
		return (launch(parser.cmd, head, ht, parser));
}
