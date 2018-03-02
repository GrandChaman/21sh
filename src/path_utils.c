/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:57:09 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/28 15:22:52 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		*ft_getcwd(void)
{
	char	*res;

	res = ft_strnew(MAXPATHLEN);
	return (getcwd(res, MAXPATHLEN));
}
