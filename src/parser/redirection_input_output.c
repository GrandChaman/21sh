/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_input_output.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:53:13 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 13:53:15 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	there_is_space_space(int *i, char *ori)
{
	while ((ori[*i] == ' ' || ori[*i] == '\n') && ori[*i])
		*i = *i + 1;
}

static int	redirections_input_2(int *i, char *ori)
{
	if (ori[*i] && ori[*i] == '>')
	{
		*i = *i + 1;
		if (ori[*i] && ori[*i] == '>')
		{
			*i = *i + 1;
			there_is_space_space(i, ori);
			if (ori[*i] == '\0' || ft_isatoken(ori[*i]))
				return (1);
			return (1);
		}
		else
		{
			there_is_space_space(i, ori);
			if (ori[*i] == '\0' || ft_isatoken(ori[*i]))
				return (1);
			return (1);
		}
	}
	return (1);
}

int			redirections_input(int *i, char *ori)
{
	if (ori[*i] && ori[*i] == '<')
	{
		*i = *i + 1;
		if (ori[*i] && ori[*i] == '<')
		{
			*i = *i + 1;
			there_is_space_space(i, ori);
			if (ori[*i] == '\0' || ft_isatoken(ori[*i]))
				return (0);
			return (3);
		}
		else
		{
			there_is_space_space(i, ori);
			if (ori[*i] == '\0' || ft_isatoken(ori[*i]))
				return (0);
			return (3);
		}
	}
	return (redirections_input_2(i, ori));
}

static int	redirections_output_2(int *i, char *ori)
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
			there_is_space_space(i, ori);
			if (ori[*i] == '\0' || ft_isatoken(ori[*i]))
				return (0);
			return (2);
		}
	}
	return (1);
}

int			redirections_output(int *i, char *ori)
{
	if (ori[*i] && ori[*i] == '<')
	{
		*i = *i + 1;
		if (ori[*i] && ori[*i] == '<')
		{
			*i = *i + 1;
			there_is_space_space(i, ori);
			if (ori[*i] == '\0' || ft_isatoken(ori[*i]))
				return (1);
			return (1);
		}
		else
		{
			there_is_space_space(i, ori);
			if (ori[*i] == '\0' || ft_isatoken(ori[*i]))
				return (1);
			return (1);
		}
	}
	return (redirections_output_2(i, ori));
}
