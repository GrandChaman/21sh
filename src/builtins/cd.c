/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:41:18 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/21 16:13:35 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int		change_dir_str(char *npath)
{
	int			res;
	struct stat	stinfo;

	res = 0;
	if (npath && access(npath, F_OK) != -1)
	{
		if (npath && stat(npath, &stinfo))
			res = (ft_fprintf(STDERR_FILENO, "cd: %s: stat error.\n",
					npath));
		else if ((stinfo.st_mode & S_IFMT) != S_IFDIR)
			res = (ft_fprintf(STDERR_FILENO, "cd: %s: Not a directory.\n",
					npath));
		else if (chdir(npath))
			res = (ft_fprintf(STDERR_FILENO, "cd: %s: Permission denied.\n",
					npath));
	}
	else if (npath)
		res = (ft_fprintf(STDERR_FILENO, "cd: %s: No such file or directory.\n",
				npath));
	return (res);
}

int				change_dir_routine(char *npath, t_env_var *home)
{
	int			res;
	char		*str;

	if (npath && npath[0] == '~')
	{
		npath++;
		str = ft_strjoin(home->value, npath);
		res = change_dir_str(str);
		free(str);
		return (res);
	}
	else
	{
		res = change_dir_str(npath);
		return (res);
	}
}

static int		builtin_cd_2(t_env_var *home)
{
	int res;

	if (!home || !home->value)
		return (ft_fprintf(STDERR_FILENO, "cd: HOME not defined.\n") && 1);
	else
		res = change_dir_str(home->value);
	return (res);
}

static int		builtin_cd_3(char *npath, char *oldpwd_path, t_env_var *home)
{
	int res;

	res = 0;
	if (npath && ft_strcmp(npath, "-") == 0)
		res = builtin_cd_1(oldpwd_path, home);
	else if (npath && ft_strcmp(npath, "-") != 0)
		res = change_dir_routine(npath, home);
	else if (!npath)
		res = builtin_cd_2(home);
	return (res);
}

int				builtin_cd(char *npath, t_list **env, t_wait_el *el)
{
	t_list			*cursor;
	t_env_var		*oldpwd;
	char			*oldpwd_path;
	t_env_var		*home;
	int				res;

	res = 0;
	cursor = NULL;
	oldpwd = NULL;
	home = NULL;
	oldpwd_path = NULL;
	el->pid = 0;
	if ((cursor = ft_lstfind(*env, "HOME", compare_with_key)))
		home = (t_env_var*)cursor->content;
	if ((cursor = ft_lstfind(*env, "OLDPWD", compare_with_key)))
		oldpwd_path = ((t_env_var*)cursor->content)->value;
	oldpwd = ft_memalloc(sizeof(t_env_var));
	oldpwd->value = ft_getcwd();
	oldpwd->key = ft_strdup("OLDPWD");
	if ((builtin_cd_3(npath, oldpwd_path, home) != 0))
		el->pid = 1;
	param_ins_or_rep(env, oldpwd);
	free(oldpwd);
	return (res);
}
