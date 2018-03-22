/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:29:35 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/22 15:40:02 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void					param_ins_or_rep(t_list **list, t_env_var *arg)
{
	t_list *cursor;

	if (!arg->value || !arg->key)
		return ;
	if ((cursor = ft_lstfind(*list, arg->key, compare_with_key)))
	{
		free(((t_env_var*)cursor->content)->value);
		((t_env_var*)cursor->content)->value = ft_strdup(arg->value);
		free(arg->key);
		free(arg->value);
	}
	else
		ft_lstpush_back(list, arg, sizeof(t_env_var));
}

void					free_env_var(void *el, size_t size)
{
	t_env_var *tmp;

	tmp = (t_env_var*)el;
	(void)size;
	free(((t_env_var*)el)->key);
	free(((t_env_var*)el)->value);
	free(el);
}

char					**list_tochar2d(t_list *list)
{
	int			i;
	int			len;
	char		**res;
	t_env_var	*tmp;
	int			var_len;

	len = ft_lstsize(list);
	res = (char**)ft_memalloc(sizeof(char*) * (len + 1));
	res[len] = NULL;
	i = -1;
	while (++i < len)
	{
		tmp = (t_env_var*)list->content;
		list = list->next;
		var_len = (tmp->key ? ft_strlen(tmp->key) : 0);
		var_len += (tmp->value ? ft_strlen(tmp->value) : 0);
		res[i] = ft_strnew(var_len + 1);
		ft_snprintf(res[i], var_len + 1, "%s=%s", tmp->key, tmp->value);
	}
	return (res);
}

t_list					*dup_environment(t_list *env)
{
	t_list		*res;
	t_env_var	tmp;

	res = NULL;
	while (env)
	{
		tmp.key = ft_strdup(((t_env_var*)env->content)->key);
		tmp.value = ft_strdup(((t_env_var*)env->content)->value);
		ft_lstpush_back(&res, &tmp, sizeof(t_env_var));
		env = env->next;
	}
	return (res);
}

void					extract_define(t_list **list, const char *param)
{
	t_env_var	res;
	int			pos;
	int			i;

	i = 0;
	if (!param || !(pos = ft_haschar((char*)param, '=')))
		return ;
	res.key = ft_strsub(param, 0, pos - 1);
	while (ft_isalnum(res.key[i]))
		i++;
	if (res.key[i])
	{
		ft_printf("%s: KEY doesn't allow non alphanumeric value\n", res.key);
		free(res.key);
		return ;
	}
	res.value = ft_strsub(param, pos, ft_strlen(param) - pos);
	param_ins_or_rep(list, &res);
	return ;
}
