/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:47:39 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 13:47:42 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <stdio.h>

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
		printf("\nparser[%d].close_stdin = %d\n", i, parser[i].close_stdin);
		printf("parser[%d].close_stdout = %d\n", i, parser[i].close_stdout);
		printf("parser[%d].close_stderr = %d\n\n", i, parser[i].close_stderr);

		printf("parser[%d].input.pipe = %d\n\n", i, parser[i].input.pipe);

		if (parser[i].input.meta)
		{
			o = 0;
			while (parser[i].input.meta)
			{
				printf("parser[%d].input.meta[%d].heredoc_number = %d\n", i, o, parser[i].input.meta[o].heredoc_number);
				printf("parser[%d].input.meta[%d].name = %s\n", i, o, parser[i].input.meta[o].name);
				/*printf("parser[%d].input.meta[%d].stdin = %d\n", i, o, parser[i].input.meta[o].stdin);
				printf("parser[%d].input.meta[%d].stdout = %d\n", i, o, parser[i].input.meta[o].stdout);
				printf("parser[%d].input.meta[%d].stderr = %d\n\n", i, o, parser[i].input.meta[o].stderr);*/
				if (parser[i].input.meta[o].next_exist == 0)
					break;
				o++;
			}
		}
		printf("parser[%d].output.pipe = %d\n", i, parser[i].output.pipe);
		if (parser[i].output.meta)
		{
			o = 0;
			while (parser[i].output.meta)
			{
				printf("parser[%d].output.meta[%d].name = %s\n", i, o, parser[i].output.meta[o].name);
			/*	printf("parser[%d].output.meta[%d].stdin = %d\n", i, o, parser[i].output.meta[o].stdin);
				printf("parser[%d].output.meta[%d].stdout = %d\n", i, o, parser[i].output.meta[o].stdout);
				printf("parser[%d].output.meta[%d].stderr = %d\n", i, o, parser[i].output.meta[o].stderr);*/
				printf("parser[%d].output.meta[%d].double_chevron = %d\n\n", i, o, parser[i].output.meta[o].double_chevron);
				if (parser[i].output.meta[o].next_exist == 0)
					break;
				o++;
			}
		}
		i++;
	}
	printf("\n------------End Parser------------\n");
}

t_parser	*get_parser(char *ori)
{
	int			stock;
	t_parser	*parser;

	stock = is_correct_talk(ori);
	if (stock == 0)
		return (NULL);
	if (stock < 0)
		return (NULL);
	if (stock == 1)
	{
		stock = count_cmd(ori);
		if (!(parser = malloc(sizeof(t_parser) * stock)))
			ft_perror("malloc", "Mallocation failed. Aborting");
		init_parser(parser, stock);
		split_evoluted(parser, ori);
		fill_parser(parser, ori);
		print_parser(parser, stock);
		return (parser);
	}
	return (NULL);
}
