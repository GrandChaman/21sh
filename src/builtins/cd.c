/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:41:18 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/01 09:16:40 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	help_norm(t_list **head, char ***setenv)
{
	if (!(*setenv = (char **)malloc(sizeof(char *) * 4)))
		exit(EXIT_FAILURE);
	(*setenv)[0] = ft_strdup("setenv");
	(*setenv)[1] = ft_strdup("OLDPWD");
	(*setenv)[2] = ft_strdup(ft_getenv(head, "PWD"));
	(*setenv)[3] = 0;
}

static int	modify_pwd(t_list **head, char **args, int i, char *oldpwd)
{
	char	**setenv;
	char	*buf;

	buf = ft_memalloc(1024);
	help_norm(head, &setenv);
	mini_setenv(setenv, head);
	free(setenv[1]);
	free(setenv[2]);
	setenv[1] = ft_strdup("PWD");
	if (ft_strcmp(args[1], "-") != 0)
		setenv[2] = ft_strdup(args[1]);
	else if (ft_strcmp(args[1], "-") == 0)
		setenv[2] = ft_strdup(oldpwd);
	else
		setenv[2] = ft_strdup(getcwd(buf, 1024));
	mini_setenv(setenv, head);
	while (setenv[++i])
		free(setenv[i]);
	free(setenv);
	free(buf);
	free(oldpwd);
	return (1);
}

int			mini_cd(char **args, t_list **head)
{
	char	*oldpwd;

	oldpwd = NULL;
	if (!args[1])
		chdir(ft_getenv(head, "HOME"));
	else
	{
		if (ft_strcmp(args[1], "-") == 0)
			if (!args[2])
			{
				oldpwd = ft_strdup(ft_getenv(head, "OLDPWD"));
				if (chdir(oldpwd) != 0)
				{
					ft_printf("minishell: dir not found / not the rights: %s\n",
					ft_getenv(head, "OLDPWD"));
					free(oldpwd);
					return (1);
				}
			}
			else
				ft_putendl("Usage: cd [-|<dir>].");
		else if (chdir(args[1]) != 0)
			return (ft_problem_dir(args[1]));
	}
	return (modify_pwd(head, args, -1, oldpwd));
}
