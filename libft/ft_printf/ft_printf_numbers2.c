/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:18:55 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/02 17:23:30 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <stdarg.h>
#include "ft_printf_format_list.h"
#include "libft.h"

int		print_binary(int fd, t_ptf_toprint format, t_ptf_param p, va_list ap)
{
	unsigned long long	n;
	int					res;
	int					len;
	char				*istr;

	res = 0;
	if (format.len)
		res += ft_putnstr(fd, format.str, format.len);
	n = extract_nb(p, ap);
	istr = ft_itoa_base(n, 2);
	len = ft_strlen(istr);
	p.padding -= ((p.hashtag && n) ? 2 : 0);
	if ((p.hashtag && n) && p.zero)
		res += ft_putnstr(fd, "0b", 2);
	res += handle_padding(fd, p, (n || p.precision ? len : -1), BEFORE);
	if ((p.hashtag && n) && !p.zero)
		res += ft_putnstr(fd, "0b", 2);
	res += (p.precision > 0 ? print_padding(fd, '0', p.precision - len) : 0);
	if (n || p.precision)
		res += ft_putnstr(fd, istr, len);
	res += handle_padding(fd, p, (n || p.precision ? len : -1), AFTER);
	free(istr);
	return (res);
}
