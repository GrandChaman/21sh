/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:34:03 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 17:34:05 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	check_pipe(t_parser *parser, int x, t_dup *r_dup)
{
	if (!(parser[x].input.pipe) && parser[x].output.pipe)
	{
		pipe(r_dup->p);
		dup2(r_dup->p[1], 1);
	}
	else if (!(parser[x].output.pipe) && parser[x].input.pipe)
	{
		close(r_dup->p[1]);
		dup2(r_dup->stdin_copy, 1);
		dup2(r_dup->p[0], 0);
	}
	else if (parser[x].input.pipe && parser[x].output.pipe)
	{
		close(r_dup->p[1]);
		dup2(r_dup->p[0], 0);
		pipe(r_dup->p);
		dup2(r_dup->p[1], 1);
	}
}
