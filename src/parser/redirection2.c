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

static int	redirections2_2(char *ori, t_vari *var)
{
	if (ori[var->i] && ori[var->i] == '>')
	{
		var->i++;
		if (ori[var->i] && ori[var->i] == '>')
		{
			var->i++;
			there_is_space(var, ori);
			if (ori[var->i] == '\0' || ft_isatoken(ori[var->i]))
				return (0);
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

int			redirections2(char *ori, t_vari *var)
{
	if (ori[var->i] && ori[var->i + 1] && (ft_isstd(ori[var->i]))
		&& (ori[var->i + 1] == '<' || ori[var->i + 1] == '>'))
		var->i++;
	if (ori[var->i] && ori[var->i] == '<')
	{
		var->i++;
		if (ori[var->i] && ori[var->i] == '<')
		{
			var->i++;
			there_is_space(var, ori);
			if (ori[var->i] == '\0' || ft_isatoken(ori[var->i]))
				return (0);
			while ((ori[var->i] != ' ' && ori[var->i] != '\n') && ori[var->i])
				var->i++;
			return (4);
		}
		else
		{
			there_is_space(var, ori);
			if (ori[var->i] == '\0' || ft_isatoken(ori[var->i]))
				return (0);
			return (3);
		}
	}
	return (redirections2_2(ori, var));
}
