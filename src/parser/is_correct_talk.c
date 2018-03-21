/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_correct_talk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:51:46 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 13:51:50 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int		this_is_word(t_vari *var, char *ori)
{
	while ((ori[var->i] != ' ' && ori[var->i] != '\n' &&
	ori[var->i] != ';' && ori[var->i] != '|') && ori[var->i])
	{
		var->boite = redirections3(&var->i, ori);
		if (var->boite == 0 && (ft_printf("21sh: syntax error\n")))
			return (0);
		if (ori[var->i] == '\0')
			return (1);
		while ((ori[var->i] == ' ' || ori[var->i] == '\n') && ori[var->i])
			var->i++;
		if ((var->stock = checkquote(&var->i, &var->o, ori)) == 'k')
			break ;
		else if (var->stock > '\0' && var->stock != 'n')
		{
			if (var->stock == '"')
				return (-1);
			else
				return (-2);
		}
		if (ori[var->i] != '<' && ori[var->i] != '>' && (var->o++))
			var->i++;
	}
	return (1);
}

static int		main_loop(t_vari *var, char *ori)
{
	while (ori[var->i] && ori[var->i] != ';' &&
		ori[var->i] != '|')
	{
		while ((ori[var->i] == ' ' || ori[var->i] == '\n') &&
			ori[var->i])
			var->i++;
		if (ori[var->i] == '\0')
			break ;
		if ((var->boite = this_is_word(var, ori)) != 1)
			return (var->boite);
		var->o = 0;
		while ((ori[var->i] == ' ' || ori[var->i] == '\n') &&
			ori[var->i])
			var->i++;
		if (ori[var->i] == '\0' || ori[var->i] == ';' ||
			ori[var->i] == '|')
			break ;
		var->z++;
	}
	return (1);
}

static int		there_is_pipe(t_vari *var, char *ori)
{
	if (ori[var->i] == '|')
	{
		var->i++;
		while ((ori[var->i] == ' ' || ori[var->i] == '\n') &&
			ori[var->i])
			var->i++;
		if (ori[var->i] == '\0')
			return (-3);
	}
	return (1);
}

static int		second_main_loop(t_vari *var, char *ori)
{
	if ((var->boite = there_is_pipe(var, ori)) != 1)
		return (var->boite);
	if (ori[var->i] == ';')
		var->i++;
	while ((ori[var->i] == ' ' || ori[var->i] == '\n') &&
		ori[var->i])
		var->i++;
	if (ori[var->i] && ft_isatoken(ori[var->i]) &&
		(ft_printf("21sh :Unexpected token %c\n", ori[var->i])))
		return (0);
	return (1);
}

int				is_correct_talk(char *ori)
{
	t_vari var;

	init_var(&var);
	while (ori[var.i])
	{
		while ((ori[var.i] == ' ' || ori[var.i] == '\n') &&
			ori[var.i])
			var.i++;
		if (ori[var.i] == '\0')
			return (0);
		if (ft_isatoken(ori[var.i]) &&
			(ft_printf("21sh :Unexpected token %c\n", ori[var.i])))
			return (0);
		var.nbr_argv = count_argv(var.i, ori);
		if ((var.boite = main_loop(&var, ori)) != 1)
			return (var.boite);
		var.z = 0;
		if (ori[var.i] == '\0')
			break ;
		if ((var.boite = second_main_loop(&var, ori)) != 1)
			return (var.boite);
		var.b++;
	}
	return (1);
}
