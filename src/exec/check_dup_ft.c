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

void	ft_easy2(int x, t_parser *parser)
{
	if (parser[x].close_stdin)
		close(0);
	if (parser[x].close_stdout)
		close(1);
	if (parser[x].close_stderr)
		close(2);
}

void	ft_easy_output(int *stock, int x, int i, t_parser *parser)
{
	if (parser[x].output.meta[i].stdin)
		*stock = 0;
	else if (parser[x].output.meta[i].stdout)
		*stock = 1;
	else if (parser[x].output.meta[i].stderr)
		*stock = 2;
}