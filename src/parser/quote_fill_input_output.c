/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_fill_input_output.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:52:49 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 13:52:51 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	checkquote_fill_output(t_vari *var, char *ori, t_parser *parser)
{
	char	tableau[3];
	int		i;
	int		stock;

	tableau[0] = '"';
	tableau[1] = '\'';
	tableau[2] = '\0';
	i = 0;
	while (tableau[i])
	{
		if (ori[var->i] == tableau[i])
		{
			stock = checkquote2_fill_output(var, ori, tableau[i], parser);
			if (stock == 0)
				return ('k');
		}
		i++;
	}
	return ('n');
}

int		checkquote2_fill_output(t_vari *var, char *ori,
	char c, t_parser *parser)
{
	int o;

	o = 0;
	if (ori[var->i] && ori[var->i] == c)
	{
		var->i++;
		while (ori[var->i] && ori[var->i] != c)
		{
			parser[var->b].output.meta[var->i_output].name[o] = ori[var->i];
			var->i++;
			o = o + 1;
		}
		parser[var->b].output.meta[var->i_output].name[o] = '\0';
		var->i++;
		var->i_output++;
		return (0);
	}
	return (1);
}

char	checkquote_fill_input(t_vari *var, char *ori, t_parser *parser)
{
	char	tableau[3];
	int		i;
	int		stock;

	tableau[0] = '"';
	tableau[1] = '\'';
	tableau[2] = '\0';
	i = 0;
	while (tableau[i])
	{
		if (ori[var->i] == tableau[i])
		{
			stock = checkquote2_fill_intput(var, ori, tableau[i], parser);
			if (stock == 0)
				return ('k');
		}
		i++;
	}
	return ('n');
}

int		checkquote2_fill_intput(t_vari *var, char *ori,
	char c, t_parser *parser)
{
	int o;

	o = 0;
	if (ori[var->i] && ori[var->i] == c)
	{
		var->i++;
		while (ori[var->i] && ori[var->i] != c)
		{
			parser[var->b].input.meta[var->i_input].name[o] = ori[var->i];
			var->i++;
			o = o + 1;
		}
		parser[var->b].input.meta[var->i_input].name[o] = '\0';
		var->i_input++;
		var->i++;
		return (0);
	}
	return (1);
}
