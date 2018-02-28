/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:54:48 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/28 15:58:10 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		print_error(const char *title, const char *message)
{
	return (ft_fprintf(2, "21sh: %s: %s\n", title, message));
}

void	ft_error(void)
{
	ft_putstr("error.\n");
	exit(EXIT_FAILURE);
}

int		ft_problem_dir(char *arg)
{
	ft_printf("minishell: dir not found / not the rights: %s\n", arg);
	return (1);
}
