/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_touch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 15:28:41 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/08 17:00:50 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		spt_arrow(unsigned long touch)
{
	move_in_terminal(touch, 1);
}
