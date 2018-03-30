/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:49:00 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/21 12:21:19 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"


void		init_parser(t_parser *parser, int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		parser[i].nb = nb;
		parser[i].cmd = NULL;
		parser[i].close_stdin = 0;
		parser[i].close_stdout = 0;
		parser[i].close_stderr = 0;
		parser[i].input.pipe = 0;
		parser[i].input.meta = NULL;
		parser[i].output.pipe = 0;
		parser[i].output.meta = NULL;
		i++;
	}
}

static void	free_cmd(t_parser *parser, int i)
{
	int o;

	o = 0;
	if (parser[i].cmd && parser[i].cmd[o])
	{
		while (parser[i].cmd[o])
		{
			free(parser[i].cmd[o]);
			o++;
		}
		free(parser[i].cmd);
	}
}

static void	free_input_meta(t_parser *parser, int i)
{
	int o;

	o = 0;
	if (parser[i].input.meta)
	{
		while (parser[i].input.meta)
		{
			free(parser[i].input.meta[o].name);
			if (parser[i].input.meta[o].next_exist == 0)
				break ;
			o++;
		}
		free(parser[i].input.meta);
	}
}

static void	free_output_meta(t_parser *parser, int i)
{
	int o;

	o = 0;
	if (parser[i].output.meta)
	{
		while (parser[i].output.meta)
		{
			free(parser[i].output.meta[o].name);
			if (parser[i].output.meta[o].next_exist == 0)
				break ;
			o++;
		}
		free(parser[i].output.meta);
	}
}

void		free_parser(t_parser *parser)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	if (parser != NULL)
	{
		if (nb == 0)
			nb = parser[0].nb;
		while (i < nb)
		{
			free_cmd(parser, i);
			free_input_meta(parser, i);
			free_output_meta(parser, i);
			i++;
		}
		free(parser);
		parser = NULL;
	}
	free(parser);
}

void	print_parser(t_parser *parser, int nb)
{
	int i;
	int o;

	o = 0;
	i = 0;
	while (i < nb)
	{
		ft_printf("\n--------------------------------------\n");
		if (parser[i].cmd != NULL)
		{
			o = 0;
			while (parser[i].cmd[o] != NULL)
			{
				ft_printf("parser[%d].cmd[%d] = %s\n", i, o, parser[i].cmd[o]);
				o++;
			}
		}
		ft_printf("\nparser[%d].close_stdin = %d\n", i, parser[i].close_stdin);
		ft_printf("parser[%d].close_stdout = %d\n", i, parser[i].close_stdout);
		ft_printf("parser[%d].close_stderr = %d\n\n", i, parser[i].close_stderr);

		ft_printf("parser[%d].input.pipe = %d\n\n", i, parser[i].input.pipe);

		if (parser[i].input.meta)
		{
			o = 0;
			while (parser[i].input.meta)
			{
				ft_printf("parser[%d].input.meta[%d].heredoc_number = %d\n", i, o, parser[i].input.meta[o].heredoc_number);
				ft_printf("parser[%d].input.meta[%d].name = %s\n", i, o, parser[i].input.meta[o].name);
				ft_printf("parser[%d].input.meta[%d].stdin = %d\n", i, o, parser[i].input.meta[o].stdin);
				ft_printf("parser[%d].input.meta[%d].stdout = %d\n", i, o, parser[i].input.meta[o].stdout);
				ft_printf("parser[%d].input.meta[%d].stderr = %d\n\n", i, o, parser[i].input.meta[o].stderr);
				if (parser[i].input.meta[o].next_exist == 0)
					break;
				o++;
			}
		}
		ft_printf("parser[%d].output.pipe = %d\n", i, parser[i].output.pipe);
		if (parser[i].output.meta)
		{
			o = 0;
			while (parser[i].output.meta)
			{
				ft_printf("parser[%d].output.meta[%d].name = %s\n", i, o, parser[i].output.meta[o].name);
				ft_printf("parser[%d].output.meta[%d].stdin = %d\n", i, o, parser[i].output.meta[o].stdin);
				ft_printf("parser[%d].output.meta[%d].stdout = %d\n", i, o, parser[i].output.meta[o].stdout);
				ft_printf("parser[%d].output.meta[%d].stderr = %d\n", i, o, parser[i].output.meta[o].stderr);
				ft_printf("parser[%d].output.meta[%d].double_chevron = %d\n\n", i, o, parser[i].output.meta[o].double_chevron);
				if (parser[i].output.meta[o].next_exist == 0)
					break;
				o++;
			}
		}
		i++;
	}
	ft_printf("\n------------End Parser------------\n");
}