/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 16:18:57 by fle-roy           #+#    #+#             */
/*   Updated: 2017/12/05 16:19:55 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		ft_numlen(unsigned int nb)
{
	if (!nb)
		return (0);
	return (ft_numlen(nb / 10) + 1);
}
