/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:58:16 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/05 18:09:53 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		backspace_command(void)
{
	move_in_terminal(T_LARR, 0);
	ft_putchar(' ');
	move_in_terminal(T_LARR, 1);
}
