/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_list.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:25:43 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/02 17:35:21 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FORMAT_LIST_H
# define FT_PRINTF_FORMAT_LIST_H
# define FLAG_LIST "-+ #0123456789.hljzcsoudixpXDIUOCS%*"
# define DONT_OVERZERO "cs%"
# define LR 0
# define UP 1
# define PTR 2
# include <stdlib.h>
# define ANSI_COLOR_RED        "\x1b[31m"
# define ANSI_COLOR_GREEN      "\x1b[32m"
# define ANSI_COLOR_YELLOW     "\x1b[33m"
# define ANSI_COLOR_BLUE       "\x1b[34m"
# define ANSI_COLOR_MAGENTA    "\x1b[35m"
# define ANSI_COLOR_CYAN       "\x1b[36m"
# define ANSI_COLOR_B_RED      "\x1b[1;31m"
# define ANSI_COLOR_B_GREEN    "\x1b[1;32m"
# define ANSI_COLOR_B_YELLOW   "\x1b[1;33m"
# define ANSI_COLOR_B_BLUE     "\x1b[1;34m"
# define ANSI_COLOR_B_MAGENTA  "\x1b[1;35m"
# define ANSI_COLOR_B_CYAN     "\x1b[1;36m"
# define ANSI_COLOR_RESET      "\x1b[0m"
# define ANSI_DEL_LINE         "\r\x1b[K"

enum							e_length_modifier {NONE, HH, H, LL, L, J, Z};

typedef struct					s_length_modifier
{
	const char					*trigger;
	enum e_length_modifier		code;

}								t_length_modifier;

typedef struct					s_color_code
{
	const char					*trigger;
	const char					*code;

}								t_color_code;

typedef struct					s_ptf_param
{
	int							hashtag;
	int							zero;
	int							minus;
	int							plus;
	int							space;
	int							padding;
	int							precision;
	int							neg;
	enum e_length_modifier		lm;

}								t_ptf_param;

typedef struct					s_ptf_toprint
{
	const char					*str;
	const char					*format;
	int							start;
	int							len;

}								t_ptf_toprint;

typedef struct					s_ptf_format
{
	const char					*trigger;
	int							(*f)(int fd, t_ptf_toprint format,
		t_ptf_param param, va_list ap);

}								t_ptf_format;

static const t_length_modifier	g_length_modifier_list[] = {
	{"hh", HH},
	{"h", H},
	{"ll", LL},
	{"l", L},
	{"j", J},
	{"z", Z},
	{NULL, NONE}
};

int								hex_handler(int fd[2], t_ptf_toprint format,
	t_ptf_param p, va_list ap);

int								print_string(int fd, t_ptf_toprint format,
	t_ptf_param param, va_list ap);
int								print_char(int fd, t_ptf_toprint format,
	t_ptf_param param, va_list ap);
int								print_pourcent(int fd, t_ptf_toprint format,
	t_ptf_param param, va_list ap);
int								print_octal(int fd, t_ptf_toprint format,
	t_ptf_param param, va_list ap);
int								print_unsigned(int fd, t_ptf_toprint format,
	t_ptf_param param, va_list ap);
int								print_signed(int fd, t_ptf_toprint format,
	t_ptf_param param, va_list ap);
int								print_hex(int fd, t_ptf_toprint format,
	t_ptf_param param, va_list ap);
int								print_hex_upper(int fd, t_ptf_toprint format,
	t_ptf_param param, va_list ap);
int								print_unsigned_upper(int fd,
	t_ptf_toprint format, t_ptf_param param, va_list ap);
int								print_signed_upper(int fd, t_ptf_toprint format,
	t_ptf_param param, va_list ap);
int								print_wchar(int fd, t_ptf_toprint format,
	t_ptf_param param, va_list ap);
int								print_wstring(int fd, t_ptf_toprint format,
	t_ptf_param param, va_list ap);
int								print_octal_upper(int fd, t_ptf_toprint format,
	t_ptf_param param, va_list ap);
int								print_pointer(int fd, t_ptf_toprint format,
	t_ptf_param param, va_list ap);
int								print_binary(int fd, t_ptf_toprint format,
	t_ptf_param p, va_list ap);

static const t_ptf_format g_format_list[] = {
	{"c", print_char},
	{"s", print_string},
	{"o", print_octal},
	{"u", print_unsigned},
	{"d", print_signed},
	{"i", print_signed},
	{"x", print_hex},
	{"p", print_pointer},
	{"b", print_binary},
	{"X", print_hex_upper},
	{"D", print_signed_upper},
	{"I", print_signed_upper},
	{"U", print_unsigned_upper},
	{"O", print_octal_upper},
	{"C", print_wchar},
	{"S", print_wstring},
	{"%", print_pourcent},
	{NULL, NULL}
};

static const t_color_code g_color_list[] = {
	{"red", ANSI_COLOR_RED},
	{"green", ANSI_COLOR_GREEN},
	{"yellow", ANSI_COLOR_YELLOW},
	{"blue", ANSI_COLOR_BLUE},
	{"magenta", ANSI_COLOR_MAGENTA},
	{"cyan", ANSI_COLOR_CYAN},
	{"bred", ANSI_COLOR_B_RED},
	{"bgreen", ANSI_COLOR_B_GREEN},
	{"byellow", ANSI_COLOR_B_YELLOW},
	{"bblue", ANSI_COLOR_B_BLUE},
	{"bmagenta", ANSI_COLOR_B_MAGENTA},
	{"bcyan", ANSI_COLOR_B_CYAN},
	{"del", ANSI_DEL_LINE},
	{"eoc", ANSI_COLOR_RESET},
	{NULL, 0}
};

#endif
