/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:31:10 by rfautier          #+#    #+#             */
/*   Updated: 2018/04/03 17:30:39 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		builtin_cd_1(char *oldpwd_path, t_env_var *home)
{
	int res;

	if (!oldpwd_path)
		res = (ft_fprintf(STDERR_FILENO, "cd: OLDPWD not defined.\n"));
	else
		res = change_dir_routine(oldpwd_path, home);
	return (res);
}

int		free_oldpwd(t_env_var *oldpwd)
{
	free(oldpwd->value);
	free(oldpwd->key);
	return (0);
}

void	set_env_post_cd(t_list **env)
{
	t_env_var *env_var;

	env_var = (t_env_var*)ft_memalloc(sizeof(t_env_var));
	env_var->value = getcwd(NULL, MAXPATHLEN);
	env_var->key = ft_strdup("PWD");
	if (env_var->value)
		param_ins_or_rep(env, env_var);
	else
		free_oldpwd(env_var);
	free(env_var);
}
