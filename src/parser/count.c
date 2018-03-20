/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:44:23 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 13:44:29 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	end_cmd(char *original, int *i, int *nb)
{
	if (original[*i] == ';' || original[*i] == '|')
	{
		*i = *i + 1;
		is_space(i, original);
		if ((original[*i] != ' ' && original[*i] != '\n') && original[*i])
			*nb = *nb + 1;
	}
}

int			count_cmd(char *original)
{
	int i;
	int nb;
	int o;

	o = 0;
	nb = 0;
	i = 0;
	while (original[i])
	{
		is_space(&i, original);
		if (original[i] == '\0')
			return (nb);
		while ((original[i] != ' ' && original[i] != '\n') && original[i])
		{
			if (nb == 0)
				nb++;
			checkquote(&i, &o, original);
			end_cmd(original, &i, &nb);
			i++;
		}
	}
	return (nb);
}

static void	redirection_input_count(char *original, int *i, int *o, int *nb)
{
	if (redirections_input(i, original) != 1)
	{
		*nb = *nb + 1;
		checkquote(i, o, original);
	}
}

static int	count_redirection_input_2(char *original, int i, int o, int nb)
{
	while (original[i])
	{
		is_space(&i, original);
		while ((original[i] != ' ' && original[i] != '\n') && original[i])
		{
			checkquote(&i, &o, original);
			is_space(&i, original);
			if (original[i] == '|' || original[i] == ';')
				return (nb);
			if (original[i] == '\0')
				break ;
			redirection_input_count(original, &i, &o, &nb);
			if (original[i] == '|' || original[i] == ';')
				return (nb);
			i++;
		}
		is_space(&i, original);
		if (original[i] == '\0')
			break ;
		if (original[i] == '|' || original[i] == ';')
			return (nb);
	}
	return (nb);
}

int			count_redirection_input(int i, char *original)
{
	int nb;
	int o;

	o = 0;
	nb = 0;
	return (count_redirection_input_2(original, i, o, nb));
}
