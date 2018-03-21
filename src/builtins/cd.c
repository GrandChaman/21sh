/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:41:18 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/01 12:45:09 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int		change_dir_routine(char *npath)
{
	int			res;
	struct stat	stinfo;

	res = -1;
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

char		*get_cwd(void)
{
	char *buf;

	buf = ft_strnew(PATH_MAX);
	if (!getcwd(buf, PATH_MAX))
	{
		free(buf);
		buf = NULL;
	}
	return (buf);
}

char					**define_to2d(t_list *list)
{
	int		i;
	int		len;
	char	**res;
	t_args	*tmp;
	int		define_len;

	len = ft_lstsize(list);
	res = (char**)ft_memalloc(sizeof(char*) * (len + 1));
	res[len] = NULL;
	i = -1;
	while (++i < len)
	{
		tmp = (t_args*)list->content;
		list = list->next;
		if (!tmp->is_define)
			continue;
		define_len = (tmp->key ? ft_strlen(tmp->key) : 0);
		define_len += (tmp->value ? ft_strlen(tmp->value) : 0);
		res[i] = ft_strnew(define_len + 1);
		ft_strcat(res[i], tmp->key);
		ft_strcat(res[i], "=");
		ft_strcat(res[i], tmp->value);
	}
	return (res);
}

int				change_dir(t_list **env, char *npath)
{
	int			res;
	char		**nenv;
	t_args		oldpwd;

	nenv = define_to2d(*env);
	res = -1;
/*	if (!npath && !(npath = (char*)ft_getenv("HOME", (const char**)nenv)))
		res = (ft_fprintf(STDERR_FILENO, "cd: HOME not defined.\n"));
	else if (!ft_strcmp(npath, "-") &&
		(oldpwd.value = (char*)ft_getenv("OLDPWD", (const char**)nenv)))
		res = change_dir(env, oldpwd.value);
	else if (!ft_strcmp(npath, "-") && !oldpwd.value)
		res = (ft_fprintf(STDERR_FILENO, "cd: OLDPWD not defined.\n"));*/
	if (npath && ft_strcmp(npath, "-"))
	{
		printf("npath = %s\n", npath);
		if ((oldpwd.value = get_cwd()))
			oldpwd.key = ft_strdup("OLDPWD");
		oldpwd.is_define = 1;
		res = change_dir_routine(npath);
	//	param_ins_or_rep(env, &oldpwd);
	}
	ft_free2d((void**)nenv);
	return (res);
}