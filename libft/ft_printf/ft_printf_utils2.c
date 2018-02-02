/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:53:42 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/02 17:28:41 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <unistd.h>
#include "libft.h"
#include <stdlib.h>
#include "ft_printf_format_list.h"

int							handle_padding(int fd, t_ptf_param param, int len,
	int att)
{
	int res;

	res = 0;
	if (((att == BEFORE && !param.minus) || (att == AFTER && param.minus))
		&& param.padding > 0 && param.padding > (param.precision - len))
		res += print_padding(fd, (param.zero ? '0' : ' '), param.padding -
		((param.precision - len <= 0 ? 0 : param.precision - len) + param.neg)
		- len);
	return (res);
}

unsigned long long			absolute_value(long long i)
{
	return ((~0 ^ (unsigned long long)i) + 1);
}

void						ft_putll(int fd, unsigned long long n, int *i)
{
	if (n > 9)
		ft_putll(fd, n / 10, i);
	ft_putchar_fd((n % 10) + '0', fd);
	(*i)++;
}

unsigned long long			extract_nb(t_ptf_param param, va_list ap)
{
	unsigned long long n;

	n = 0;
	if (param.lm == NONE)
		n = (unsigned long long)va_arg(ap, unsigned int);
	else if (param.lm == HH)
		n = (unsigned long long)((unsigned char)va_arg(ap, unsigned int));
	else if (param.lm == H)
		n = (unsigned long long)((unsigned short)va_arg(ap, unsigned int));
	else if (param.lm == L || param.lm == Z || param.lm == J)
		n = (unsigned long long)va_arg(ap, unsigned long);
	else if (param.lm == LL)
		n = (unsigned long long)va_arg(ap, unsigned long long);
	return (n);
}

unsigned long long			extract_nb_signed(t_ptf_param *param, va_list ap)
{
	long long n;

	n = 0;
	if (param->lm == NONE)
		n = (long long)va_arg(ap, int);
	else if (param->lm == HH)
		n = (long long)((char)(va_arg(ap, int)));
	else if (param->lm == H)
		n = (long long)((short)(va_arg(ap, int)));
	else if (param->lm == L || param->lm == Z || param->lm == J)
		n = (long long)va_arg(ap, long);
	else if (param->lm == LL)
		n = (long long)va_arg(ap, long long);
	if (n < 0)
	{
		n = (long long)absolute_value(n);
		param->neg = 1;
	}
	else
		param->neg = 0;
	return ((unsigned long long)n);
}
