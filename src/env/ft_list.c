/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 11:29:15 by vbaudot           #+#    #+#             */
/*   Updated: 2018/04/07 02:09:04 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		ft_lstprint(t_list **head)
{
	t_list	*curr;

	if (head != NULL)
	{
		curr = *head;
		while (curr)
		{
			if (curr->content)
				ft_putendl(curr->content);
			curr = curr->next;
		}
	}
}

t_list		*create_list_from_env(char **env)
{
	t_list	*tmp;
	t_list	*head;
	t_list	*tmp2;
	int		x;

	x = 0;
	if (*env != NULL)
	{
		tmp = ft_lstnew(env[x], ft_strlen(env[x]));
		head = tmp;
		while (env[++x])
		{
			tmp2 = ft_lstnew(env[x], ft_strlen(env[x]));
			tmp->next = tmp2;
			tmp = tmp2;
		}
	}
	else
	{
		tmp = ft_lstnew("PATH=/bin:/usr/bin", ft_strlen("PATH=/bin:/usr/bin"));
		head = tmp;
	}
	return (head);
}

int			list_len(t_list **head)
{
	t_list	*curr;
	int		len;

	len = 1;
	if (*head != NULL)
	{
		curr = *head;
		while (curr)
		{
			len++;
			curr = curr->next;
		}
	}
	return (len);
}

char		**create_env_from_list(t_list **head)
{
	t_list	*curr;
	char	**env;
	int		i;

	i = 0;
	env = (char **)ft_memalloc(sizeof(char *) * list_len(head));
	if (*head != NULL)
	{
		curr = *head;
		while (curr)
		{
			env[i++] = ft_strdup(curr->content);
			curr = curr->next;
		}
	}
	env[i] = NULL;
	return (env);
}
