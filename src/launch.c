/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:40:22 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/20 17:28:17 by fle-roy          ###   ########.fr       */
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

int			launch(char **args, t_list **head, t_bin_hash_table *ht)
{
	pid_t	pid;
	int		status;
	t_bin_hash *bin;
	char	**env;

	status = 0;
	bin = get_elem_from_ht(ht, args[0]);
	if (!bin)
	{
		ft_printf("21sh: %s: No such command.\n", args[0]);
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		env = list_tochar2d(*head);
		execve(bin->path, &args[0], env);
		return (0);
	}
	else if (pid < 0)
		ft_putendl("minishell: fork error\n");
	else
		waitpid(pid, &status, WUNTRACED);
	return (status);
}
