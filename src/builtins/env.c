/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:26:47 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/02 11:45:28 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	has_equal_sign(char *str, int *x)
{
	int i;
	int y;

	i = -1;
	y = 0;
	if (str != NULL)
		while (str[++i])
		{
			if (str[i] == '=')
			{
				*x = y;
				return (1);
			}
			y++;
		}
	return (0);
}

static int	help_norm(t_list **head, char ***setenv, char **args)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (has_equal_sign(args[++i], &x) == 1)
	{
		if (!(*setenv = (char **)malloc(sizeof(char *) * (4))))
			return (1);
		(*setenv)[3] = 0;
		(*setenv)[0] = ft_strdup("setenv");
		(*setenv)[1] = ft_strsub(args[i], 0, x);
		(*setenv)[2] = ft_strsub(args[i], x + 1,
			ft_strlen(args[i]) - (x + 1));
		mini_setenv(*setenv, head);
		x = -1;
		while ((*setenv)[++x])
			free((*setenv)[x]);
		free(*setenv);
	}
	execute_env(&args[i], head);
	return (1);
}

static int	help_norm_2(t_list **head, char ***setenv, char **args)
{
	ft_lsterase(head);
	*head = NULL;
	if (args[2] != NULL)
		return (help_norm(head, setenv, &args[1]));
	return (1);
}

int			mini_env(char **args, t_list **head)
{
	char	**setenv;

	if (!args[1])
		ft_lstprint(head);
	if (ft_strcmp(args[1], "-i") == 0)
		return (help_norm_2(head, &setenv, args));
	else if (args[1])
		return (help_norm(head, &setenv, args));
	return (1);
}
