/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:26:47 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/20 13:13:20 by fle-roy          ###   ########.fr       */
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

int			builtin_env(t_list **env, char **args)
{
	int arg_offset;

	arg_offset = 1;
	if (!args[arg_offset])
		print_env(*env);
	else
	{
		if (!ft_strcmp(args[arg_offset], "-i") && arg_offset++)
			ft_lstdel(env, free_env_var);
		while (args[arg_offset++])
			extract_define(&list, args[arg_offset - 1])
		//BETA
		int i;

		i = 0;
		ft_fprintf(get_ft_shell()->debug_tty, "Exec : ");
		while (args[++i])
			ft_fprintf(get_ft_shell()->debug_tty, "%s ", args[i]);
		ft_fprintf(get_ft_shell()->debug_tty, "\n");
		//launch(args + 1, env);
	}
	return (0);
}
