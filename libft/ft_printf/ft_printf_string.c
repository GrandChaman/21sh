/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:04:53 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/02 17:36:39 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include <stdarg.h>
#include "ft_printf_format_list.h"
#include "libft.h"

char	*get_null_str(int empty)
{
	if (empty)
		return ("");
	return ("(null)");
}

int		print_string(int fd, t_ptf_toprint format, t_ptf_param p, va_list ap)
{
	char	*str;
	int		res;
	int		len;

	res = 0;
	if (p.lm == L)
		return (print_wstring(fd, format, p, ap));
	if (format.len)
		res += ft_putnstr(fd, format.str, format.len);
	if (!(str = va_arg(ap, char *)))
		str = get_null_str(!p.precision);
	len = ft_strlen(str);
	p.padding += (!p.precision && len ? len : 0);
	p.precision = (p.precision > len ? len : p.precision);
	if (!p.minus && p.padding > 0)
		res += print_padding(fd, (p.zero ? '0' : ' '), p.padding
		- (p.precision <= 0 ? len : p.precision));
	if (p.precision && len)
		res += ft_putnstr(fd, str, p.precision < 0 ? 0 : p.precision);
	else if (!p.precision && !ft_strcmp(str, "(null)") && !p.zero)
		res += ft_putnstr(fd, " ", 0);
	if (p.minus && p.padding > 0)
		res += print_padding(fd, (p.zero ? '0' : ' '), p.padding -
		(p.precision <= 0 ? len : p.precision));
	return (res);
}

int		print_char(int fd, t_ptf_toprint format, t_ptf_param param, va_list ap)
{
	char	c;
	int		res;

	res = 0;
	if (param.lm == L)
		return (print_wchar(fd, format, param, ap));
	if (format.len)
		res += ft_putnstr(fd, format.str, format.len);
	c = (char)va_arg(ap, int);
	if (!param.minus && param.padding > 0)
		res += print_padding(fd, (param.zero ? '0' : ' '), param.padding - 1);
	if (c)
		res += ft_putnstr(fd, &c, 1);
	else
	{
		ft_putchar_fd('\0', fd);
		res++;
	}
	if (param.minus && param.padding > 0)
		res += print_padding(fd, (param.zero ? '0' : ' '), param.padding -
		(param.precision > 0 ? param.precision : 1));
	return (res);
}

int		print_pourcent(int fd, t_ptf_toprint format, t_ptf_param param,
	va_list ap)
{
	int res;

	res = 0;
	if (format.len)
		res += ft_putnstr(fd, format.str, format.len);
	(void)ap;
	if (!param.minus && param.padding > 0)
		res += print_padding(fd, (param.zero ? '0' : ' '), param.padding - 1);
	res += ft_putnstr(fd, "%", 0);
	if (param.minus && param.padding > 0)
		res += print_padding(fd, ' ', param.padding - 1);
	return (res);
}
