/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:53:36 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 13:53:38 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	redirections2_2(char *original, t_vari *var)
{
	if (original[var->i] && original[var->i] == '>')
	{
		var->i++;
		if (original[var->i] && original[var->i] == '>')
		{
			var->i++;
			there_is_space(var, original);
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
			return (2);
		}
		else
		{
			there_is_space(var, original);
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
			return (2);
		}
	}
	return (1);
}

int			redirections2(char *original, t_vari *var)
{
	if (original[var->i] && original[var->i + 1] && (ft_isstd(original[var->i]))
		&& (original[var->i + 1] == '<' || original[var->i + 1] == '>'))
		var->i++;
	if (original[var->i] && original[var->i] == '<')
	{
		var->i++;
		if (original[var->i] && original[var->i] == '<')
		{
			var->i++;
			there_is_space(var, original);
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
			while ((original[var->i] != ' ' && original[var->i] != '\n') && original[var->i])
				var->i++;
			return (4);
		}
		else
		{
			there_is_space(var, original);
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
			return (3);
		}
	}
	return (redirections2_2(original, var));
}
