/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dup_ft.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:33:33 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/23 13:53:05 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	ft_easy2(t_parser parser, int x_meta, int is_input)
{
	if (is_input)
	{
		if (parser.input.meta[x_meta].stdin)
			close(0);
		if (parser.input.meta[x_meta].stdout)
			close(1);
		if (parser.input.meta[x_meta].stderr)
			close(2);
	}
	else
	{
		if (parser.output.meta[x_meta].stdin)
			close(0);
		if (parser.output.meta[x_meta].stdout)
			close(1);
		if (parser.output.meta[x_meta].stderr)
			close(2);
	}
}

void	ft_easy_output(int *stock, int i, t_parser parser)
{
	if (parser.output.meta[i].stdin)
		*stock = 0;
	else if (parser.output.meta[i].stdout)
		*stock = 1;
	else if (parser.output.meta[i].stderr)
		*stock = 2;
}
