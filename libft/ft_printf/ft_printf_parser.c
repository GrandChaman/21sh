/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:53:42 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/02 17:13:08 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_parser.h"
#include "ft_printf_utils.h"
#include "ft_printf_format_list.h"
#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>

t_ptf_param		parse_param(const char *format, va_list ap)
{
	t_ptf_param res;

	init_param(&res);
	parse_length_modifier(format, &res);
	parse_numbers(format, &res, ap);
	parse_flags(format, &res);
	return (res);
}

t_ptf_toprint	get_toprint(const char *format, int start, int stop)
{
	t_ptf_toprint res;

	res.format = format + stop + 1;
	res.str = format + start;
	res.start = start;
	res.len = stop - start;
	return (res);
}

int				format_handler(int fd, t_ptf_toprint format, int *i, va_list ap)
{
	int				ii;
	t_ptf_format	fmt;
	int				l;
	int				tmp;
	t_ptf_param		param;

	ii = -1;
	param = parse_param(format.format, ap);
	tmp = skip_to_format(format.format);
	*i += tmp + 1;
	format.format += tmp;
	l = 0;
	while (g_format_list[++ii].f)
	{
		tmp = ft_strccmp(g_format_list[ii].trigger, format.format);
		if (tmp > l)
		{
			l = tmp;
			fmt = g_format_list[ii];
		}
	}
	if (l == 0 || !fmt.f)
		return (0);
	*i += l;
	return (fmt.f(fd, format, param, ap));
}
