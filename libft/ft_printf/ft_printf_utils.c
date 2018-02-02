/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:53:42 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/02 17:06:11 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <unistd.h>
#include "libft.h"
#include <stdlib.h>

int					ft_nblen(unsigned long long nb)
{
	if (!nb)
		return (0);
	return (ft_nblen(nb / 10) + 1);
}

int					print_padding(int fd, char c, int len)
{
	char	tmp[PADDING_BUF_SIZE + 1];
	int		res;

	res = 0;
	if (len <= 0)
		return (0);
	if (len > PADDING_BUF_SIZE)
	{
		res += print_padding(fd, c, (len - PADDING_BUF_SIZE));
		len -= (len - PADDING_BUF_SIZE);
	}
	ft_memset(tmp, c, len);
	tmp[len] = '\0';
	write(fd, tmp, len);
	return (res + len);
}

int					ft_strccmp(const char *lhs, const char *rhs)
{
	int i;

	i = 0;
	while (lhs[i] == rhs[i] && lhs[i] && rhs[i])
		i++;
	return (i);
}

int					ft_strnccmp(const char *lhs, const char *rhs, int max)
{
	int i;

	i = 0;
	while (lhs[i] == rhs[i] && lhs[i] && rhs[i] && i < max)
		i++;
	return (i);
}

int					ft_putnstr(int fd, const char *str, int stop)
{
	int i;

	i = 0;
	while (str[i] && (!stop || i < stop))
		i++;
	write(fd, str, i);
	return (i);
}
