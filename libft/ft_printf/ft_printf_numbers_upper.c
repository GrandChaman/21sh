/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers_upper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:18:55 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/02 17:37:04 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <stdarg.h>
#include "ft_printf_format_list.h"
#include "libft.h"

int		print_octal_upper(int fd, t_ptf_toprint format, t_ptf_param param,
	va_list ap)
{
	param.lm = L;
	return (print_octal(fd, format, param, ap));
}

int		print_unsigned_upper(int fd, t_ptf_toprint format, t_ptf_param param,
	va_list ap)
{
	param.lm = L;
	return (print_unsigned(fd, format, param, ap));
}

int		print_signed_upper(int fd, t_ptf_toprint format, t_ptf_param param,
	va_list ap)
{
	param.lm = L;
	return (print_signed(fd, format, param, ap));
}

int		hex_handler(int m[2], t_ptf_toprint format, t_ptf_param p,
	va_list ap)
{
	unsigned long long	n;
	int					res;
	int					len;
	char				*istr;

	res = 0;
	if (format.len)
		res += ft_putnstr(m[0], format.str, format.len);
	n = extract_nb(p, ap);
	istr = ft_itoa_base(n, 16);
	if (m[1] == LR || m[1] == PTR)
		ft_strtolower(istr);
	len = ft_strlen(istr);
	p.padding -= (m[1] == PTR || (p.hashtag && (n || m[1] == PTR)) ? 2 : 0);
	if ((m[1] == PTR || (p.hashtag && n)) && p.zero)
		res += ft_putnstr(m[0], (m[1] == LR || m[1] == PTR ? "0x" : "0X"), 2);
	res += handle_padding(m[0], p, (n || p.precision ? len : -1), BEFORE);
	if ((m[1] == PTR || (p.hashtag && n)) && !p.zero)
		res += ft_putnstr(m[0], (m[1] == LR || m[1] == PTR ? "0x" : "0X"), 2);
	res += (p.precision > 0 ? print_padding(m[0], '0', p.precision - len) : 0);
	if (n || p.precision)
		res += ft_putnstr(m[0], istr, len);
	res += handle_padding(m[0], p, (n || p.precision ? len : -1), AFTER);
	free(istr);
	return (res);
}

int		print_hex_upper(int fd, t_ptf_toprint format, t_ptf_param param,
	va_list ap)
{
	int fd_n_mode[2];

	fd_n_mode[0] = fd;
	fd_n_mode[1] = UP;
	return (hex_handler(fd_n_mode, format, param, ap));
}
