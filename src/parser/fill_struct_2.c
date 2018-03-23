/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:13:25 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 14:13:27 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	fill_backslashzero(t_vari *var, t_parser *parser)
{
	if (var->z >= 0 && var->o != 0 && var->box == 1 && var->boite != 4)
	{
		parser[var->b].cmd[var->j][var->o] = '\0';
		var->j++;
	}
	if (var->box == 2 && var->o != 0)
	{
		parser[var->b].output.meta[var->i_output].name[var->o] = '\0';
		var->i_output++;
		var->box = 1;
	}
	if (var->box == 3 && var->o != 0)
	{
		parser[var->b].input.meta[var->i_input].name[var->o] = '\0';
		var->i_input++;
		var->box = 1;
	}
}

void	fill_it(t_vari *var, t_parser *parser, char *ori)
{
	if (var->boite == 1 && var->box == 1)
	{
		parser[var->b].cmd[var->j][var->o] = ori[var->i];
	}
	if (var->box == 3)
	{
		parser[var->b].input.meta[var->i_input].name[var->o] = ori[var->i];
	}
	if (var->box == 2)
	{
		parser[var->b].output.meta[var->i_output].name[var->o] = ori[var->i];
	}
}
