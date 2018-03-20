/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_evoluted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:54:06 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 13:54:11 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void malloc_meta(t_vari *var, t_parser *parser)
{
	if (var->boite == 2)
	{
		if (var->i_output == 0)
		{
			if (!(parser[var->b].output.meta = malloc(sizeof(t_meta_output) * var->nbr_redirection_output + 1)))
				exit(0);
			init_meta_output(parser, var->b, var->nbr_redirection_output);
		}
	}
	if (var->boite == 3 || var->boite == 4)
	{
		if (var->i_input == 0)
		{
			if (!(parser[var->b].input.meta = malloc(sizeof(t_meta_input) * var->nbr_redirection_input + 1)))
				exit(0);
			init_meta_input(parser, var->b, var->nbr_redirection_input);
		}
		if (var->boite == 4)
			var->i_input++;
	}
}

static void	malloc_all(t_vari *var, t_parser *parser, char *ori)
{
	if (var->z == 0 && var->box == 1)
	{
		if (!(parser[var->b].cmd = malloc(sizeof(char *) * var->nbr_argv + 1)))
			exit(0);
	}
	if (var->box == 1)
	{
		if (!(parser[var->b].cmd[var->z] = malloc(sizeof(char) * var->o + 1)))
			exit(0);
	}
	if (var->box == 2)
	{
		while ((ori[var->i] != ' ' && ori[var->i] != '\n' &&
		ori[var->i] != ';' && ori[var->i] != '|') && ori[var->i])
		{
			var->i++;
			var->o++;
		}
		if (!(parser[var->b].output.meta[var->i_output].name = malloc(sizeof(char) * var->o + 1)))
			exit(0);
		var->i_output++;
	}
	if (var->box == 3)
	{
		while ((ori[var->i] != ' ' && ori[var->i] != '\n' &&
		ori[var->i] != ';' && ori[var->i] != '|') && ori[var->i])
		{
			var->i++;
			var->o++;
		}
		if (!(parser[var->b].input.meta[var->i_input].name = malloc(sizeof(char) * var->o + 1)))
			exit(0);
		var->i_input++;
	}
}

static void	there_is_pipe(t_vari *var, t_parser *parser, char *ori)
{
	if (ori[var->i] == '|')
	{
		parser[var->b].output.pipe = 1;
		var->i++;
		while ((ori[var->i] == ' ' || ori[var->i] == '\n') && ori[var->i])
			var->i++;
		parser[var->b + 1].input.pipe = 1;
	}
}

static void there_is_word(t_vari *var, t_parser *parser, char *ori)
{
	while ((ori[var->i] != ' ' && ori[var->i] != '\n' &&
	ori[var->i] != ';' && ori[var->i] != '|') && ori[var->i])
	{
		if ((checkquote(&var->i, &var->o, ori)) == 'k')
			break ;
		if (ori[var->i] == '\0')
			break ;
		var->boite = redirections2(ori, var);
		if (var->boite != 1)
		{
			malloc_meta(var, parser);
			checkquote(&var->i, &var->o, ori);
			var->box = var->boite;
			break ;
		}
		var->i++;
		var->o++;
	}
}

static void there_is_an_cmd(t_vari *var, t_parser *parser, char *ori)
{
	while (ori[var->i] && ori[var->i] != ';' && ori[var->i] != '|')
	{
		there_is_space(var, ori);
		if (ori[var->i] == '\0')
			break ;
		there_is_word(var, parser, ori);
		malloc_all(var, parser, ori);
		var->o = 0;
		there_is_space(var, ori);
		if (ori[var->i] == '\0' || ori[var->i] == ';' || ori[var->i] == '|')
			break ;
		if (var->box == 1)
			var->z++;
		var->box = 1;
	}
}

void	split_evoluted(t_parser *parser, char *ori)
{

	t_vari var;
	init_var(&var);

	while (ori[var.i])
	{
		var.box = 1;
		there_is_space(&var, ori);
		var.nbr_argv = count_argv(var.i, ori);
		var.nbr_redirection_input = count_redirection_input(var.i, ori);
		var.nbr_redirection_output = count_redirection_output(var.i, ori);
		there_is_an_cmd(&var, parser, ori);
		var.z = 0;
		var.i_input = 0;
		var.i_output = 0;
		if (ori[var.i] == '\0')
			break ;
		there_is_pipe(&var, parser, ori);
		if (ori[var.i] == ';')
			var.i++;
		there_is_space(&var, ori);
		var.b++;
	}
}
