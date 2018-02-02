/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:38:11 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/02 17:35:43 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_utils.h"
#include "ft_printf_parser.h"
#include "libft.h"
#include <stdarg.h>

int		handle_colors(int fd, const char *format, int *li, int *i)
{
	int ii;
	int len;
	int res;

	res = 0;
	ii = -1;
	len = *i + 1;
	while (format[len] && format[len] != '}')
		len++;
	while (g_color_list[++ii].trigger && format[len] == '}')
		if (!ft_strncmp(g_color_list[ii].trigger, format + *i + 1,
			len - *i - 1))
		{
			if ((*i) - *li)
				res += ft_putnstr(fd, format + *li, (*i) - *li);
			res += ft_putnstr(fd, g_color_list[ii].code, 0);
			*li = len + 1;
			*i = len;
			break ;
		}
	return (res);
}

int		ft_printf_routine(int fd, const char *ft, va_list ap)
{
	int		i;
	int		li;
	int		tmp;
	int		res;

	res = 0;
	li = 0;
	i = -1;
	while (ft[++i])
		if (ft[i] == '%')
		{
			if ((tmp = format_handler(fd, get_toprint(ft, li, i), &i, ap)) >= 0)
				res += tmp;
			else
				return (-1);
			li = i;
			i--;
		}
		else if (ft[i] == '{')
			res += handle_colors(fd, ft, &li, &i);
	res += ft_putnstr(fd, ft + li,
		(i && ft[i - 1] == '%' ? (i - li) - 1 : 0));
	return (res);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		res;

	if (!format)
		return (-1);
	va_start(ap, format);
	res = ft_printf_routine(1, format, ap);
	va_end(ap);
	return (res);
}

int		ft_fprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		res;

	if (!format)
		return (-1);
	va_start(ap, format);
	res = ft_printf_routine(fd, format, ap);
	va_end(ap);
	return (res);
}
