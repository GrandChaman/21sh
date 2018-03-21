/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 13:25:54 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/21 15:24:27 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				builtin_setenv(char **args, t_list **env)
{
	t_env_var	e_var;
	char		*tmp;

	tmp = NULL;
	if (!args[1] || (args[1] && !(tmp = ft_strchr(args[1], '=')) && !args[2]))
		return (ft_printf("Usage: setenv KEY[=VALUE] [VALUE]\n") && 1);
	if (tmp)
	{
		e_var.key = ft_strsub(args[1], 0, (int)(tmp - args[1]));
		e_var.value = ft_strdup(tmp + 1);
	}
	else
	{
		e_var.key = ft_strdup(args[1]);
		e_var.value = ft_strdup(args[2]);
	}
	param_ins_or_rep(env, &e_var);
	return (0);
}

int				builtin_unsetenv(char **args, t_list **env)
{
	t_list	*tmp;

	if (!args[1])
		return (ft_printf("Usage: unsetenv KEY\n") && 1);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(((t_env_var*)tmp->content)->key, args[1]))
		{
			ft_lstdelone(&tmp, free_env_var);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}
