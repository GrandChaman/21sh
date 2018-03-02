/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 10:16:54 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/02 10:16:56 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	init_parser(t_parser *parser, int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		parser[i].nb = nb;
		parser[i].cmd = NULL;
		parser[i].input.exist = 0;
		parser[i].input.pipe = 0;
		parser[i].input.name_file = NULL;
		parser[i].output.standart = 0;
		parser[i].output.erreur = 0;
		parser[i].output.to_next_cmd = 0;
		parser[i].output.double_chevron = 0;
		parser[i].output.name_file = NULL;
		parser[i].output.exist = 0;
		i++;
	}
}

void	free_parser(t_parser *parser)
{
	int i;
	int nb;
	int o;

	i = 0;
	nb = 0;
	if (parser != NULL)
	{
		if (nb == 0)
			nb = parser[0].nb;
		while (i < nb)
		{
			o = 0;
			if (parser[i].cmd)
			{
				while (parser[i].cmd[o])
				{
					free(parser[i].cmd[o]);
					o++;
				}
			}
			if (parser[i].input.name_file)
				free(parser[i].input.name_file);
			if (parser[i].output.name_file)
				free(parser[i].output.name_file);
			i++;
		}
	}
}

void	print_parser(t_parser *parser, int nb)
{
	int i;
	int o;

	o = 0;
	i = 0;
	printf("\n\n	Structure du parser		\n\n");
	while (i < nb)
	{
		printf("\n\n");
		if (parser[i].cmd != NULL)
		{
			o = 0;
			while (parser[i].cmd[o] != NULL)
			{
				printf("parser[%d].cmd[%d] = %s\n", i, o, parser[i].cmd[o]);
				o++;
			}
		}
		else
			printf("Pas d argument\n");
		printf("\nparser[%d].input.exist = %d\n", i, parser[i].input.exist);
		printf("parser[%d].input.pipe = %d\n", i, parser[i].input.pipe);
		printf("parser[%d].input.name_file = %s\n\n", i, parser[i].input.name_file);

		printf("parser[%d].output.standart = %d\n", i, parser[i].output.standart);
		printf("parser[%d].output.erreur = %d\n", i, parser[i].output.erreur);
		printf("parser[%d].output.to_next_cmd = %d\n", i, parser[i].output.to_next_cmd);
		printf("parser[%d].output.double_chevron = %d\n", i, parser[i].output.double_chevron);
		printf("parser[%d].output.name_file = %s\n", i, parser[i].output.name_file);
		i++;
	}
}
