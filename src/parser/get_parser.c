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

void		create_file(t_parser parser)
{
	int fd;
	int i;

	i = 0;
	while (parser.output.meta)
	{
		if (parser.output.meta[i].name[0] != '&')
		{
			if ((fd = open(parser.output.meta[i].name, O_RDWR |
				O_CREAT | O_EXCL, 0777)) != -1)
				close(fd);
		}
		if (parser.output.meta[i].next_exist == 0)
			break ;
		i++;
	}
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
		if ((fill_parser(parser, ori)) == -1)
		{
			if (parser)
				free_parser(parser);
			return (NULL);
		}
		return (parser);
	}
	return (NULL);
}
