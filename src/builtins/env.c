/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:26:47 by vbaudot           #+#    #+#             */
/*   Updated: 2018/04/03 17:59:18 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		print_env(t_list *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", ((t_env_var*)env->content)->key,
			((t_env_var*)env->content)->value);
		env = env->next;
	}
}

static void	init_env_var(int *arg_offset, int *status)
{
	*arg_offset = 1;
	*status = 0;
}

int			builtin_env(t_list **env, char **args, t_parser parser)
{
	int					arg_offset;
	int					status;
	t_wait_el			el;

	init_env_var(&arg_offset, &status);
	if (!args[arg_offset])
		print_env(*env);
	else
	{
		if (!ft_strcmp(args[arg_offset], "-i") && ++arg_offset)
			ft_lstdel(env, free_env_var);
		while (args[arg_offset] && ft_haschar(args[arg_offset], '='))
			extract_define(env, (const char**)args, &arg_offset);
		if (*(args + arg_offset))
		{
			el = launch(args + arg_offset, env, get_ft_shell()->ht, parser);
			if (el.pid < 0)
				return (-1);
			waitpid(el.pid, &status, WUNTRACED);
			return (status);
		}
		else
			print_env(*env);
	}
	return (0);
}
