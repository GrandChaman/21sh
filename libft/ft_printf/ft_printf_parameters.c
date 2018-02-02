/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parameters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 17:46:22 by fle-roy           #+#    #+#             */
/*   Updated: 2017/11/30 15:13:01 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "libft.h"
#include "ft_printf_parser.h"
#include "ft_printf_extract_dynamic_param.h"
#include <stdarg.h>

void			init_param(t_ptf_param *param)
{
	param->hashtag = 0;
	param->zero = 0;
	param->minus = 0;
	param->plus = 0;
	param->space = 0;
	param->padding = -1;
	param->precision = -1;
	param->neg = 0;
	param->lm = NONE;
}

int				skip_to_format(const char *str)
{
	int i;
	int ii;

	i = 0;
	while (str[i] && is_arguments(str + i))
	{
		ii = -1;
		while (g_format_list[++ii].trigger)
			if (ft_strccmp(g_format_list[ii].trigger, &str[i]))
				return (i);
		i++;
	}
	return (i);
}

void			parse_length_modifier(const char *fmt, t_ptf_param *param)
{
	int i;
	int len;
	int ii;
	int t;

	i = 0;
	param->lm = NONE;
	while (is_arguments(fmt + i) && (!i || !is_format_identifier(fmt + i - 1)))
	{
		ii = -1;
		len = 0;
		while (g_length_modifier_list[++ii].trigger)
		{
			t = ft_strccmp(g_length_modifier_list[ii].trigger, fmt + i);
			if (t - ft_strlen(g_length_modifier_list[ii].trigger) == 0
				&& t > len)
			{
				len = t;
				param->lm = g_length_modifier_list[ii].code;
			}
		}
		i += len + (!len ? 1 : 0);
	}
}

void			parse_flags(const char *fmt, t_ptf_param *param)
{
	int i;

	i = 0;
	while (is_arguments(fmt + i) && (!i || !is_format_identifier(fmt + i - 1)))
	{
		if (fmt[i] == '#')
			param->hashtag = 1;
		else if (fmt[i] == ' ')
			param->space = 1;
		else if (fmt[i] == '-')
			param->minus = 1;
		else if (fmt[i] == '+')
			param->plus = 1;
		else if (fmt[i] == '0' && (!i || (!ft_isdigit(fmt[i - 1]) &&
				fmt[i - 1] != '.')))
			param->zero = 1;
		i++;
	}
	if (param->plus)
		param->space = 0;
	if ((param->minus || param->precision >= 0) && i &&
		!should_override_zero(fmt[i - 1]))
		param->zero = 0;
}

void			parse_numbers(const char *fmt, t_ptf_param *param, va_list ap)
{
	int i;
	int in_nb;

	in_nb = 0;
	i = 0;
	param->precision = -1;
	param->padding = -1;
	while (is_arguments(fmt + i) && (!i || !is_format_identifier(fmt + i - 1)))
	{
		if (!(ft_isdigit(fmt[i])))
			in_nb = 0;
		if (!in_nb && ft_isdigit(fmt[i]) &&
			(!i || fmt[i - 1] != '.'))
			param->padding = ft_atoi(fmt + i);
		else if (i && fmt[i - 1] == '.')
			param->precision = (ft_isdigit(fmt[i]) ? ft_atoi(fmt + i) : 0);
		if (fmt[i] == '*' && fmt[i - 1] != '.')
			param->padding = extract_dyn_param(&(param->minus), ap);
		if (fmt[i] == '*' && fmt[i - 1] == '.')
			param->precision = extract_dyn_param(NULL, ap);
		if (ft_isdigit(fmt[i]))
			in_nb = 1;
		i++;
	}
}
