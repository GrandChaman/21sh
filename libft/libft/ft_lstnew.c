/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:08:48 by bluff             #+#    #+#             */
/*   Updated: 2018/03/01 12:43:20 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*el;

	if (!(el = (t_list*)malloc(sizeof(t_list))))
		ft_perror("malloc", "Mallocation failed. Aborting");
	if (content)
	{
		el->content = ft_strdup(content);
		el->content_size = content_size;
	}
	else
	{
		el->content = NULL;
		el->content_size = 0;
	}
	el->next = NULL;
	el->prev = NULL;
	return (el);
}
