/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:53:54 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/23 15:05:56 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		there_is_space(t_vari *var, char *ori)
{
	while ((ori[var->i] == ' ' || ori[var->i] == '\n')
		&& ori[var->i])
		var->i++;
}

static int	redirections4_2(t_vari *var, t_parser *parser, char *ori)
{
	if (ori[var->i] && ori[var->i] == '>')
	{
		fill_std_o(var, parser, ori);
		var->i++;
		if (ori[var->i] && ori[var->i] == '>')
		{
			var->i++;
			there_is_space(var, ori);
			if (ori[var->i] == '\0' || ft_isatoken(ori[var->i]))
				return (0);
			parser[var->b].output.meta[var->i_output].double_chevron = 1;
			return (2);
		}
		else
		{
			there_is_space(var, ori);
			if (ori[var->i] == '\0' || ft_isatoken(ori[var->i]))
				return (0);
			return (2);
		}
	}
	return (1);
}

static int	is_heredoc(char *ori, t_parser *parser, t_vari *var)
{
	var->i++;
	there_is_space(var, ori);
	if (ori[var->i] == '\0' || ft_isatoken(ori[var->i]))
		return (0);
	var->heredoc++;
	parser[var->b].input.meta[var->i_input].heredoc_number = var->heredoc;
	if ((call_heredoc(var, ori)) == -1)
		return (-1);
	there_is_space(var, ori);
	return (4);
}

int			redirections4(char *ori, t_parser *parser, t_vari *var)
{
	if (ori[var->i] && ori[var->i + 1] && (ft_isstd(ori[var->i]))
		&& (ori[var->i + 1] == '<' || ori[var->i + 1] == '>'))
		var->i++;
	if (ori[var->i] && ori[var->i] == '<')
	{
		fill_std_i(var, parser, ori);
		var->i++;
		if (ori[var->i] && ori[var->i] == '<')
			return (is_heredoc(ori, parser, var));
		else
		{
			there_is_space(var, ori);
			if (ori[var->i] == '\0' || ft_isatoken(ori[var->i]))
				return (0);
			return (3);
		}
	}
	return (redirections4_2(var, parser, ori));
}
