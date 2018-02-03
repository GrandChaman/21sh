/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:57:09 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/03 13:10:12 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <sys/param.h>

char		*ft_getcwd(void)
{
	char	*res;

	res = ft_strnew(MAXPATHLEN);
	return (getcwd(res, MAXPATHLEN));
}
