/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:33:45 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 17:36:46 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	is_fd(int x, t_parser *parser, int i)
{
	int stock;

	stock = 0;
	if (!(parser[x].output.meta[i].name[1] &&
		parser[x].output.meta[i].name[1] == '-'))
	{
		ft_easy_output(&stock, x, i, parser);
		if (parser[x].output.meta[i].name[1])
		{
			if (dup2(stock, parser[x].output.meta[i].name[1] - 48) == -1)
				exit(0);
		}
		else
		{
			if (dup2(stock, 1) == -1)
				exit(0);
		}
	}
}

static int	is_d_chevron(int x, t_parser *parser, int i)
{
	int fd;

	if ((fd = open(parser[x].output.meta[i].name, O_RDWR | O_CREAT
		| O_EXCL | O_APPEND, 0777)) == -1)
	{
		if ((fd = open(parser[x].output.meta[i].name,
			O_RDWR | O_APPEND, 0777)) == -1)
			exit(0);
	}
	return (fd);
}

static int	normal(int x, t_parser *parser, int i)
{
	int fd;

	if ((fd = open(parser[x].output.meta[i].name, O_WRONLY |
		O_TRUNC, 0777)) == -1)
		exit(0);
	close(fd);
	if ((fd = open(parser[x].output.meta[i].name, O_RDWR, 0777)) == -1)
		exit(0);
	return (fd);
}

static void	sinon(int x, t_parser *parser, int i)
{
	int fd;
	int stock;

	stock = 0;
	if (parser[x].output.meta[i].double_chevron)
		fd = is_d_chevron(x, parser, i);
	else if ((fd = open(parser[x].output.meta[i].name,
		O_RDWR | O_CREAT | O_EXCL, 0777)) == -1)
		fd = normal(x, parser, i);
	ft_easy_output(&stock, x, i, parser);
	if (dup2(fd, stock) == -1)
		exit(0);
}

int			check_dup(t_parser *parser, int x)
{
	int i;

	i = 0;
	if (parser[x].output.meta)
	{
		while (parser[x].output.meta)
		{
			if (parser[x].output.meta[i].name[0] == '&')
				is_fd(x, parser, i);
			else
				sinon(x, parser, i);
			if (parser[x].output.meta[i].next_exist == 0)
				break ;
			i++;
		}
	}
	return (check_dup_input(parser, x));
}
