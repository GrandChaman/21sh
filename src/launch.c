/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:40:22 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/20 13:03:54 by fle-roy          ###   ########.fr       */
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

int			launch(char **args, t_list **head)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**env;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		ft_fprintf(get_ft_shell()->debug_tty, "SALUT\n");
		env = list_tochar2d(*head);
		path = (check_slash(args[0]) == 1) ? ft_strdup(args[0]) :
		ft_strdup(ft_path(head, args[0]));
		ft_fprintf(get_ft_shell()->debug_tty, "path : %s\n", path);
		execve(path, &args[0], env);
		free(path);
		return (0);
	}
	else if (pid < 0)
		ft_putendl("minishell: fork error\n");
	else
		waitpid(pid, &status, WUNTRACED);
	return (status);
}
