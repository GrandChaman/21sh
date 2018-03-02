/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:16:38 by vbaudot           #+#    #+#             */
/*   Updated: 2018/02/28 15:19:50 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			mini_exit(char **args)
{
	ft_putendl("exit");
	if (args[1])
	{
		ft_putendl("exit: Too many arguments");
		return (1);
	}
	return (0);
}
