/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 10:42:42 by fle-roy           #+#    #+#             */
/*   Updated: 2017/11/29 17:42:54 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_PARSER_H
# define FT_PRINTF_PARSER_H
# include <stdarg.h>
# include <stdlib.h>
# include "ft_printf_format_list.h"

void			parse_flags(const char *fmt, t_ptf_param *param);
void			parse_length_modifier(const char *fmt, t_ptf_param *param);
void			parse_numbers(const char *fmt, t_ptf_param *param, va_list ap);
int				skip_to_format(const char *str);
void			init_param(t_ptf_param *param);
t_ptf_toprint	get_toprint(const char *format, int start, int stop);

#endif
