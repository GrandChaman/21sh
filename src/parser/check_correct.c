/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_correct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:43:50 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 13:43:52 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	*check_correct(char *original)
{
	int			stock;
	char		*prompt;

	stock = is_correct(original);
	if (stock < 0)
	{
		if (stock == -1)
			prompt = "d-quotes>";
		if (stock == -2)
			prompt = "s-quotes>";
		if (stock == -3)
			prompt = "commands>";
		return (prompt);
	}
	if (stock == 0)
		return (NULL);
	if (stock == 1)
		return (NULL);
	return (NULL);
}
