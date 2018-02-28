/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 09:21:09 by vbaudot           #+#    #+#             */
/*   Updated: 2018/02/28 15:29:50 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		ft_lsterase(t_list **head)
{
	t_list	*tmp;

	while (*head)
	{
		tmp = *head;
		free((*head)->content);
		*head = (*head)->next;
		free(tmp);
	}
	*head = NULL;
}

void		ft_lstdelthis_bis(t_list **head, t_list **prev, t_list **curr)
{
	free((*curr)->content);
	if ((*curr)->next)
	{
		(*prev)->next = (*curr)->next;
		free((*curr));
		*prev = (*prev)->next;
		*curr = (*prev)->next;
	}
	else
	{
		free(*curr);
		if (*prev != *head)
		{
			(*prev)->next = NULL;
			*curr = *prev;
		}
		else
			*head = NULL;
	}
}

void		ft_lstdelthis(t_list **head, char *str)
{
	t_list	*prev;
	t_list	*curr;
	int		len;

	curr = *head;
	prev = curr;
	len = ft_strlen(str);
	while (curr)
	{
		if (ft_strncmp(curr->content, str, len) == 0 &&
		((char *)curr->content)[len] == '=')
			ft_lstdelthis_bis(head, &prev, &curr);
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
