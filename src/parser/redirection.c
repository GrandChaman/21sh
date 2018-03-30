/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:53:24 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 13:53:26 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	there_is_space_space(int *i, char *ori)
{
	while ((ori[*i] == ' ' || ori[*i] == '\n') && ori[*i])
		*i = *i + 1;
}

static int	redirections3_2(int *i, char *ori)
{
	if (ori[*i] && ori[*i] == '>')
	{
		*i = *i + 1;
		if (ori[*i] && ori[*i] == '>')
		{
			*i = *i + 1;
			there_is_space_space(i, ori);
			if (ori[*i] == '\0' || ft_isatoken(ori[*i]))
				return (0);
			return (2);
		}
		else
		{
			if (ori[*i] && ori[*i + 1] && ori[*i] == '&')
			{
				if (!ft_isstd(ori[*i + 1]) || (ft_isstd(ori[*i + 1])
					&& (ori[*i + 2] != ' ' && (ori[*i + 2] != '\n')
					&& ori[*i + 2] != '\0')))
					return (0);
					if (!ori[*i + 1] || (ori[*i + 1] == ' ' || ori[*i + 1] == '\n'))
						return (0);
			}
			if (ori[*i] == '&' && !ori[*i + 1])
				return (0);
			there_is_space_space(i, ori);
			if (ori[*i] == '\0' || ft_isatoken(ori[*i]))
				return (0);
			return (2);
		}
	}
	return (1);
}

static int	double_chevron_2(int *i, char *ori)
{
	*i = *i + 1;
	there_is_space_space(i, ori);
	if (ori[*i] == '\0' || ft_isatoken(ori[*i]))
		return (0);
	while ((ori[*i] != ' ' && ori[*i] != '\n') && ori[*i])
	{
		if (ori[*i] == '\'' || ori[*i] == '"')
			return (0);
		*i = *i + 1;
	}
	return (1);
}

static int	just_one_chevron(int *i, char *ori)
{
	if (ori[*i] && ori[*i + 1] && ori[*i] == '&')
	{
		if (!ft_isstd(ori[*i + 1]) || (ft_isstd(ori[*i + 1])
			&& (ori[*i + 2] != ' ' && (ori[*i + 2] != '\n')
			&& ori[*i + 2] != '\0')))
			return (0);
		if (!ori[*i + 1] || (ori[*i + 1] == ' ' || ori[*i + 1] == '\n'))
			return (0);
	}
	if (ori[*i] == '&' && !ori[*i + 1])
		return (0);
	there_is_space_space(i, ori);
	if (ori[*i] == '\0' || ft_isatoken(ori[*i]))
		return (0);
	return (3);
}

int			redirections3(int *i, char *ori)
{
	if (ori[*i] && ori[*i + 1] && (ft_isstd(ori[*i])) &&
		(ori[*i + 1] == '<' || ori[*i + 1] == '>'))
	{
		if (ori[*i - 1] != ' ')
			return (0);
		*i = *i + 1;
	}
	else if (*i != 0 && ori[*i - 1] != ' ' && ori[*i - 1] != '\n'
		&& (ori[*i] == '<' ||
		ori[*i] == '>'))
		return (0);
	if (ori[*i] && ori[*i] == '<')
	{
		*i = *i + 1;
		if (ori[*i] && ori[*i] == '<')
			return (double_chevron_2(i, ori));
		else
			return (just_one_chevron(i, ori));
	}
	return (redirections3_2(i, ori));
}
