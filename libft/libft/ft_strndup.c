/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 00:12:49 by bluff             #+#    #+#             */
/*   Updated: 2018/03/14 18:02:15 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(const char *str, size_t n)
{
	char	*nstr;
	size_t	len;

	if (!str || !n)
		return (NULL);
	len = ft_strlen(str) + 1;
	len = (len > n ? len : n + 1);
	if (!(nstr = (char*)malloc(sizeof(char) * n)))
		ft_perror("malloc", "Mallocation failed. Aborting");
	ft_strncpy(nstr, str, n);
	return (nstr);
}
