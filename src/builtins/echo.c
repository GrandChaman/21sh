/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:38:38 by vbaudot           #+#    #+#             */
/*   Updated: 2018/04/03 13:55:14 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				write_echo_special_codes(char *args, int *cursor)
{
	if (*args == 'a')
		write(STDOUT_FILENO, "\a", 1);
	else if (*args == 'b')
		write(STDOUT_FILENO, "\b", 1);
	else if (*args == 'c')
		return (0);
	else if (*args == 'f')
		write(STDOUT_FILENO, "\f", 1);
	else if (*args == 'n')
		write(STDOUT_FILENO, "\n", 1);
	else if (*args == 'r')
		write(STDOUT_FILENO, "\r", 1);
	else if (*args == 't')
		write(STDOUT_FILENO, "\t", 1);
	else if (*args == 'v')
		write(STDOUT_FILENO, "\v", 1);
	else if (*args == '\\')
		write(STDOUT_FILENO, "\\", 1);
	else if (*args == '0')
		ft_printf("%c", ft_atoi_base(args, "01234567"));
	(*cursor) += 1;
	while (ft_isdigit((*args)++))
		(*cursor)++;
	return (1);
}

int				builtin_echo(char **args, t_list **env)
{
	int i;
	int ii;
	int should_print_nl;

	(void)env;
	if (!args[1])
		return (-1 * ft_printf("\n"));
	should_print_nl = (!ft_strcmp(args[1], "-n") ? 0 : 1);
	i = !should_print_nl;
	while (args[++i] && (ii = -1))
	{
		if (i != 1 && should_print_nl)
			write(STDOUT_FILENO, " ", 1);
		while (args[i][++ii])
			if (args[i][ii] == '\\')
			{
				if (!write_echo_special_codes(&(args[i][ii + 1]), &ii))
					return (-1);
			}
			else
				write(STDOUT_FILENO, &(args[i][ii]), 1);
	}
	if (should_print_nl)
		write(STDOUT_FILENO, "\n", 1);
	return (-1);
}
