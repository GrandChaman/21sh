/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_evoluted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 10:16:51 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/02 10:16:52 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		ft_isatoken(char c)
{
	if (c == ';' || c == '&' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

void	split_evoluted(t_parser *parser, char *original)
{
	int i;
	int o;
	int z;
	int b;
	char stock;
	int nbr_argv;
	int boite;

	b = 0;
	z = 0;
	o = 0;
	i = 0;
//	printf("\noriginal = %s\n\n", original);
	while (original[i])
	{
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		nbr_argv = count_argv(i, original) + 2;
//		printf("\nnbr_argv = %d\n", nbr_argv);
		while (original[i] && original[i] != ';' && original[i] != '|')
		{
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0')
				break;
			while ((original[i] != ' ' && original[i] != '\t' &&
			original[i] != ';' && original[i] != '|') && original[i])
			{
				boite = redirections2(&i, original, parser, b);
				while ((original[i] == ' ' || original[i] == '\t') && original[i])
					i++;
				stock = checkquote(&i, &o, original);
				if (stock == 'k')
					break ;
				i++;
				o++;
			}
			if (z == 0 && boite == 1)
			{
		//		printf("nbr_argv = %d\n", nbr_argv);
				if (!(parser[b].cmd = malloc(sizeof(char *) * nbr_argv)))
					exit(0);
			}
			if (boite == 1)
			{
				if (!(parser[b].cmd[z] = malloc(sizeof(char) * o + 1)))
					exit(0);
			}
			if (boite == 2)
			{
				if (!(parser[b].output.name_file = malloc(sizeof(char) * o + 1)))
					exit(0);
			}
			if (boite == 3)
			{
				if (!(parser[b].input.name_file = malloc(sizeof(char) * o + 1)))
					exit(0);
			}

			printf("commande [%d] mot[%d] = %d\n", b, z, o);
			o = 0;
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0' || original[i] == ';' || original[i] == '|')
				break ;
			z++;
		}
		z = 0;
		if (original[i] == '\0')
			break ;
		if (original[i] == '|')
		{
			parser[b].output.to_next_cmd = 1;
			i++;
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			parser[b + 1].input.pipe = 1;
		}
		if (original[i] == ';')
			i++;
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		b++;
	}
}
