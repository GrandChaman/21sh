/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:45:02 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 13:45:05 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		is_space(int *i, char *ori)
{
	while ((ori[*i] == ' ' || ori[*i] == '\n') && ori[*i])
		*i = *i + 1;
}

static void	redirection_count(char *ori, int *i, int *o, int *nb)
{
	if (redirections_output(i, ori) != 1)
	{
		*nb = *nb + 1;
		checkquote(i, o, ori);
	}
}

static int	count_redirection_output_2(char *ori, int i, int o, int nb)
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
			redirection_count(ori, &i, &o, &nb);
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

int			count_redirection_output(int i, char *ori)
{
	int nb;
	int o;

	o = 0;
	nb = 0;
	return (count_redirection_output_2(ori, i, o, nb));
}
