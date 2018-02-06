/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:57:06 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/03 16:28:17 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		is_env_correct(void)
{
	int res;

	res = tgetent(NULL, getenv("TERM"));
	if (res == -1)
		return (!ft_fprintf(2,
			"TERM environment variable is not set or is incorrect.\n"));
	else if (res == 0)
		return (!ft_fprintf(2,
			"TERM info database not found.\n"));
	return (1);
}
