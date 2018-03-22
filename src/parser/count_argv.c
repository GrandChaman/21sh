/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:45:28 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/22 14:20:22 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	main_loop(int *i, int o, int *nb, char *ori)
{
	while ((checkquote(i, &o, ori)) == 'k')
	{
		*nb = *nb + 1;
		while ((ori[*i] == ' ' || ori[*i] == '\n') && ori[*i])
			*i = *i + 1;
	}
	while ((ori[*i] == ' ' || ori[*i] == '\n') && ori[*i])
		*i = *i + 1;
}

static void	space(int *i, char *ori)
{
	while ((ori[*i] == ' ' || ori[*i] == '\n') && ori[*i])
		*i = *i + 1;
}

static int	main_loop2(int i, int o, int nb, char *ori)
{
	while (ori[i])
	{
		space(&i, ori);
		while ((ori[i] != ' ' && ori[i] != '\n') && ori[i])
		{
			main_loop(&i, o, &nb, ori);
			if (ori[i] == '|' || ori[i] == ';')
				break ;
			if (ori[i] == '\0' && (nb = nb - 1))
				break ;
			if ((redirections3(&i, ori)) != 1 &&
				(checkquote(&i, &o, ori)))
				nb = nb - 1;
			if (ori[i] == '|' || ori[i] == ';' || ori[i] == '\0')
				return (nb);
			i++;
			if (ori[i] && (ori[i] == '\'' || ori[i] == '"'))
				break ;
		}
		nb++;
		space(&i, ori);
		if (ori[i] == '\0')
			break ;
		if (ori[i] == '|' || ori[i] == ';')
			return (nb);
	}
	return (nb);
}

int			count_argv(int i, char *ori)
{
	int nb;
	int o;

	o = 0;
	nb = 0;
	return (main_loop2(i, o, nb, ori));
}
