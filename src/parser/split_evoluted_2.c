/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_evoluted_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:09:44 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 14:09:47 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	malloc_meta(t_vari *var, t_parser *parser)
{
	if (var->boite == 2)
	{
		if (var->i_output == 0)
		{
			if (!(parser[var->b].output.meta = malloc(sizeof(t_meta_output)
				* var->nbr_redirection_output + 1)))
				exit(0);
			init_meta_output(parser, var->b, var->nbr_redirection_output);
		}
	}
	if (var->boite == 3 || var->boite == 4)
	{
		if (var->i_input == 0)
		{
			if (!(parser[var->b].input.meta = malloc(sizeof(t_meta_input)
				* var->nbr_redirection_input + 1)))
				exit(0);
			init_meta_input(parser, var->b, var->nbr_redirection_input);
		}
		if (var->boite == 4)
			var->i_input++;
	}
}

void	there_is_pipe_2(t_vari *var, t_parser *parser, char *ori)
{
	if (ori[var->i] == '|')
	{
		parser[var->b].output.pipe = 1;
		var->i++;
		while ((ori[var->i] == ' ' || ori[var->i] == '\n') && ori[var->i])
			var->i++;
		parser[var->b + 1].input.pipe = 1;
	}
}
