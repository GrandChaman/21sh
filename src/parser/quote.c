/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:52:16 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 13:52:18 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	checkquote(int *i, int *o, char *ori)
{
	char	tableau[3];
	int		var;
	int		stock;

	tableau[0] = '"';
	tableau[1] = '\'';
	tableau[2] = '\0';
	var = 0;
	while (tableau[var])
	{
		if (ori[*i] == tableau[var])
		{
			stock = checkquote2(i, o, ori, tableau[var]);
			if (stock == 0)
				return ('k');
			if (stock == -1)
				return (tableau[var]);
		}
		var++;
	}
	return ('n');
}

int		checkquote2(int *i, int *o, char *ori, char c)
{
	if (ori[*i] && ori[*i] == c)
	{
		*i = *i + 1;
		while (ori[*i] && ori[*i] != c)
		{
			*i = *i + 1;
			*o = *o + 1;
		}
		if (ori[*i] == '\0' && ori[*i] != c)
			return (-1);
		*i = *i + 1;
		return (0);
	}
	return (1);
}

char	checkquote_fill_cmd(t_vari *var, char *ori, t_parser *parser)
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
			stock = checkquote2_fill_cmd(var, ori, tableau[i], parser);
			if (stock == 0)
				return ('k');
		}
		i++;
	}
	return ('n');
}

int		checkquote2_fill_cmd(t_vari *var, char *ori, char c,
	t_parser *parser)
{
	int o;

	o = 0;
	if (ori[var->i] && ori[var->i] == c)
	{
		var->i++;
		while (ori[var->i] && ori[var->i] != c)
		{
			parser[var->b].cmd[var->j][o] = ori[var->i];
			var->i++;
			o = o + 1;
		}
		parser[var->b].cmd[var->j][o] = '\0';
		var->j++;
		var->i++;
		return (0);
	}
	return (1);
}
