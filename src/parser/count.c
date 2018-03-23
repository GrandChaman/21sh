/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:44:23 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/23 18:58:55 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	end_cmd(char *ori, int *i, int *nb)
{
	if (ori[*i] == ';' || ori[*i] == '|')
	{
		*i = *i + 1;
		is_space(i, ori);
		if ((ori[*i] != ' ' && ori[*i] != '\n') && ori[*i])
			*nb = *nb + 1;
	}
}

int			count_cmd(char *ori)
{
	int i;
	int nb;
	int o;

	o = 0;
	nb = 0;
	i = 0;
	while (ori[i])
	{
		is_space(&i, ori);
		if (ori[i] == '\0')
			return (nb);
		while ((ori[i] != ' ' && ori[i] != '\n') && ori[i])
		{
			if (nb == 0)
				nb++;
			checkquote(&i, &o, ori);
			if (!ori[i])
				return (nb) ;
			end_cmd(ori, &i, &nb);
			if (!ori[i++])
				return (nb) ;
		}
	}
	return (nb);
}

static void	redirection_input_count(char *ori, int *i, int *o, int *nb)
{
	if (redirections_input(i, ori) != 1)
	{
		*nb = *nb + 1;
		checkquote(i, o, ori);
	}
}

static int	count_redirection_input_2(char *ori, int i, int o, int nb)
{
	while (ori[i])
	{
		is_space(&i, ori);
		while ((ori[i] != ' ' && ori[i] != '\n') && ori[i])
		{
			checkquote(&i, &o, ori);
			is_space(&i, ori);
			if (ori[i] == '|' || ori[i] == ';')
				return (nb);
			if (ori[i] == '\0')
				break ;
			redirection_input_count(ori, &i, &o, &nb);
			if (ori[i] == '|' || ori[i] == ';')
				return (nb);
			i++;
		}
		is_space(&i, ori);
		if (ori[i] == '\0')
			break ;
		if (ori[i] == '|' || ori[i] == ';')
			return (nb);
	}
	return (nb);
}

int			count_redirection_input(int i, char *ori)
{
	int nb;
	int o;

	o = 0;
	nb = 0;
	return (count_redirection_input_2(ori, i, o, nb));
}
