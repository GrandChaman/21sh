/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:31:10 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/25 17:31:15 by rfautier         ###   ########.fr       */
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
