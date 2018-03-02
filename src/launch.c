/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:40:22 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/02 11:16:33 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	check_slash(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '/')
			return (1);
	return (0);
}

int			launch(t_parser parser, t_list **head)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**env;

	pid = fork();
	if (pid == 0)
	{
		env = create_env_from_list(head);
		path = (check_slash(parser.cmd[0]) == 1) ? ft_strdup(parser.cmd[0]) :
		ft_strdup(ft_path(head, parser.cmd[0]));
		execve(path, &parser.cmd[0], env);
		free(path);
		return (0);
	}
	else if (pid < 0)
		ft_putendl("minishell: fork error\n");
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}
