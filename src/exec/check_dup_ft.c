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

void	init_r_dup(t_dup *r_dup)
{
	if ((r_dup->stdin_copy = dup(0)) == -1)
		exit(0);
	if ((r_dup->stdout_copy = dup(1)) == -1)
		exit(0);
	if ((r_dup->stderr_copy = dup(2)) == -1)
		exit(0);
}

void	init_dup(t_dup *r_dup)
{
	if ((dup2(r_dup->stdin_copy, 0)) == -1)
		exit(0);
	if ((dup2(r_dup->stdout_copy, 1)) == -1)
		exit(0);
	if ((dup2(r_dup->stderr_copy, 2)) == -1)
		exit(0);
}
