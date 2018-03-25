/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 17:16:42 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/22 15:36:37 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void					char2d_tolist(t_list **env, char **args)
{
	int			i;
	t_env_var	var;
	char		*equal;

	i = -1;
	while (args[++i])
	{
		equal = ft_strchr(args[i], '=');
		if (!equal)
			continue ;
		var.key = ft_strsub(args[i], 0, (int)(equal - args[i]));
		var.value = ft_strsub(args[i], (int)(equal - args[i]) + 1,
			ft_strlen(args[i]) - (int)(equal - args[i]));
		ft_lstpush_back(env, &var, sizeof(t_env_var));
	}
}

int						compare_with_key(void *e1, void *e2)
{
	t_env_var	*tmp;
	char		*cmp;

	tmp = (t_env_var*)e1;
	cmp = (char*)e2;
	return (ft_strcmp(tmp->key, cmp));
}

int						check_if_key_ok(t_env_var e_var, int i, t_wait_el *el)
{
	if (!ft_isalnum(e_var.key[i]))
	{
		free(e_var.key);
		el->pid = 1;
		return (ft_printf("KEY doesn't allow "
			"non alphanumeric value\n") && 1);
	}
	return (0);
}
