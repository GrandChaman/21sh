/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:26:47 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/21 16:23:06 by fle-roy          ###   ########.fr       */
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
	t_bin_hash_table *ht;

	arg_offset = 1;
	if (!args[arg_offset])
		print_env(*env);
	else
	{
		if (!ft_strcmp(args[arg_offset], "-i") && ++arg_offset)
			ft_lstdel(env, free_env_var);
		while (args[arg_offset])
			extract_define(env, args[arg_offset++]);
		ht = load_bin_into_hash_table(*env);
		if (*(args + arg_offset))
			launch(args + arg_offset, env, ht);
		else
			print_env(*env);
		free_hash_table(&ht);
	}
	return (0);
}
