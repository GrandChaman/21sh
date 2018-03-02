/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 13:25:54 by vbaudot           #+#    #+#             */
/*   Updated: 2018/02/28 15:20:03 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		ft_lst_add_or_modify(int flag, t_list **head,
	char *name, char *value)
{
	t_list	*curr;
	char	*str;

	curr = *head;
	while (curr)
	{
		if (ft_strncmp(curr->content, name, ft_strlen(name)) == 0 &&
		((char *)curr->content)[ft_strlen(name)] == '=')
		{
			free(curr->content);
			curr->content = ft_str3join(name, "=", value);
			flag = 1;
		}
		curr = curr->next;
	}
	if (flag == 0)
	{
		str = ft_str3join(name, "=", value);
		if (*head == NULL)
			*head = ft_lstnew(str, ft_strlen(str));
		else
			ft_lstappend(head, ft_lstnew(str, ft_strlen(str)));
		free(str);
	}
}

int			mini_setenv(char **args, t_list **head)
{
	int		i;

	i = -1;
	if (!args[1])
		ft_lstprint(head);
	else
	{
		while (args[1][++i])
			if (args[1][i] == '=')
			{
				ft_putendl("minishell: setenv: variable name is not valid.");
				return (1);
			}
		if (args[2] != NULL && args[3] != NULL)
			return (too_many_args("setenv"));
		i = 0;
		if (args[2] != NULL)
			ft_lst_add_or_modify(0, head, args[1], args[2]);
		else
			ft_lst_add_or_modify(0, head, args[1], "");
	}
	return (1);
}

int			mini_unsetenv(char **args, t_list **head)
{
	int		j;

	if (!args[1])
		ft_lstprint(head);
	j = 0;
	while (args[++j])
	{
		if (ft_strcmp(args[j], "*") == 0)
		{
			ft_lsterase(head);
			return (1);
		}
		ft_lstdelthis(head, args[j]);
	}
	return (1);
}
