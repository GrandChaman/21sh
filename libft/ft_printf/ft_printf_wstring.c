/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_wstring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:04:53 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/02 17:23:19 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <stdarg.h>
#include "ft_printf_format_list.h"
#include "libft.h"
#include <wchar.h>
#include <unistd.h>

int		ft_putwchar(int fd, unsigned int c)
{
	int				res;
	int				i;
	unsigned char	byte;

	if (c <= 127 || MB_CUR_MAX == 1)
		write(fd, &c, 1);
	else if (c < 2048 || MB_CUR_MAX == 2)
		byte = ((((unsigned int)c >> 6) << 27) >> 27 | WCHAR_1);
	else if ((c > 2047 && c < 65536) || MB_CUR_MAX == 3)
		byte = (((((unsigned int)c >> 12) << 28) >> 28) | WCHAR_2);
	else
		byte = (((((unsigned int)c >> 18) << 29) >> 29) | WCHAR_3);
	if (c <= 127 || MB_CUR_MAX == 1)
		return (1);
	write(fd, &byte, 1);
	i = 1 + ((c > 2047 && c < 65536) ? 1 : 0) + (c > 65536 ? 2 : 0);
	i += (i >= MB_CUR_MAX ? (i - MB_CUR_MAX - 1) : 0);
	res = i + 1;
	while (--i >= 0)
	{
		byte = ((((c >> (i * 6)) << 26) >> 26) | WCHAR_GEN);
		write(fd, &byte, 1);
	}
	return (res);
}

int		print_wchar(int fd, t_ptf_toprint format, t_ptf_param param, va_list ap)
{
	unsigned int		c;
	int					res;

	res = 0;
	c = va_arg(ap, unsigned int);
	if (!is_utf8(c))
		return (-1);
	if (format.len)
		res += ft_putnstr(fd, format.str, format.len);
	if (c > 255 && c < 2048)
		param.padding -= 1;
	else if ((c > 2047 && c < 65536))
		param.padding -= 2;
	else if (c > 65535 && c < 2097152)
		param.padding -= 3;
	else if (c > 2097151)
		param.padding -= 4;
	res += handle_padding(fd, param, 1, BEFORE);
	res += ft_putwchar(fd, c);
	res += handle_padding(fd, param, 1, AFTER);
	return (res);
}

int		ft_putwstr(int fd, wchar_t *c, int len)
{
	int res;
	int i;
	int o;
	int tmp;

	i = 0;
	o = 0;
	res = 0;
	while (c[i] && (o <= len || len < 0))
	{
		tmp = wchar_length((unsigned int)c[i]);
		if ((o + tmp <= len) || (len < 0))
			res += ft_putwchar(fd, (unsigned int)c[i]);
		o += tmp;
		i++;
	}
	return (res);
}

int		print_wstring(int fd, t_ptf_toprint format, t_ptf_param p, va_list ap)
{
	wchar_t		*c;
	int			res;
	int			i;
	int			len;

	len = 0;
	i = -1;
	res = 0;
	if (format.len)
		res += ft_putnstr(fd, format.str, format.len);
	if (!(c = va_arg(ap, wchar_t *)))
		c = L"(null)";
	while (c[++i] && (i < p.precision || p.precision < 0))
		if (!is_utf8((unsigned int)c[i]))
			return (-1);
	len = ft_strwlen(c, p.precision);
	p.padding += (len < p.precision || (len < p.precision && !len)
	? p.precision - len : 0) + (!p.precision ? 1 : 0);
	res += handle_padding(fd, p, (len = (!len ? 1 : len)), BEFORE);
	if (!len && p.padding > 0)
		res += print_padding(fd, ' ', 1);
	else
		res += ft_putwstr(fd, c, p.precision);
	res += handle_padding(fd, p, len, AFTER);
	return (res);
}
