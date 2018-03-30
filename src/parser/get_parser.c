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
		if ((fill_parser(parser, ori)) == -1)
		{
			if (parser)
				free_parser(parser);
			return (NULL);
		}
		//print_parser(parser, stock);
		return (parser);
	}
	return (NULL);
}
