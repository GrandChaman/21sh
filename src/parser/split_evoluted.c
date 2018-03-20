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

static void	malloc_all(t_vari *var, t_parser *parser, char *original)
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
		while ((original[var->i] != ' ' && original[var->i] != '\n' &&
		original[var->i] != ';' && original[var->i] != '|') && original[var->i])
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
		while ((original[var->i] != ' ' && original[var->i] != '\n' &&
		original[var->i] != ';' && original[var->i] != '|') && original[var->i])
		{
			var->i++;
			var->o++;
		}
		if (!(parser[var->b].input.meta[var->i_input].name = malloc(sizeof(char) * var->o + 1)))
			exit(0);
		var->i_input++;
	}
}

static void	there_is_pipe(t_vari *var, t_parser *parser, char *original)
{
	if (original[var->i] == '|')
	{
		parser[var->b].output.pipe = 1;
		var->i++;
		while ((original[var->i] == ' ' || original[var->i] == '\n') && original[var->i])
			var->i++;
		parser[var->b + 1].input.pipe = 1;
	}
}

static void there_is_word(t_vari *var, t_parser *parser, char *original)
{
	while ((original[var->i] != ' ' && original[var->i] != '\n' &&
	original[var->i] != ';' && original[var->i] != '|') && original[var->i])
	{
		if ((checkquote(&var->i, &var->o, original)) == 'k')
			break ;
		if (original[var->i] == '\0')
			break ;
		var->boite = redirections2(original, var);
		if (var->boite != 1)
		{
			malloc_meta(var, parser);
			checkquote(&var->i, &var->o, original);
			var->box = var->boite;
			break ;
		}
		var->i++;
		var->o++;
	}
}

static void there_is_an_cmd(t_vari *var, t_parser *parser, char *original)
{
	while (original[var->i] && original[var->i] != ';' && original[var->i] != '|')
	{
		there_is_space(var, original);
		if (original[var->i] == '\0')
			break ;
		there_is_word(var, parser, original);
		malloc_all(var, parser, original);
		var->o = 0;
		there_is_space(var, original);
		if (original[var->i] == '\0' || original[var->i] == ';' || original[var->i] == '|')
			break ;
		if (var->box == 1)
			var->z++;
		var->box = 1;
	}
}

void	split_evoluted(t_parser *parser, char *original)
{

	t_vari var;
	init_var(&var);

	while (original[var.i])
	{
		var.box = 1;
		there_is_space(&var, original);
		var.nbr_argv = count_argv(var.i, original);
		var.nbr_redirection_input = count_redirection_input(var.i, original);
		var.nbr_redirection_output = count_redirection_output(var.i, original);
		there_is_an_cmd(&var, parser, original);
		var.z = 0;
		var.i_input = 0;
		var.i_output = 0;
		if (original[var.i] == '\0')
			break ;
		there_is_pipe(&var, parser, original);
		if (original[var.i] == ';')
			var.i++;
		there_is_space(&var, original);
		var.b++;
	}
}
