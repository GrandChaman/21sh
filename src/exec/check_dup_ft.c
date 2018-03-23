/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dup_ft.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:33:33 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 17:33:36 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	ft_easy2(t_parser parser)
{
	if (parser.close_stdin)
		close(0);
	if (parser.close_stdout)
		close(1);
	if (parser.close_stderr)
		close(2);
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