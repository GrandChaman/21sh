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
				ft_perror("dup", "Dup failed. Aborting");
		}
		else
		{
			if (dup2(stock, 1) == -1)
				ft_perror("dup", "Dup failed. Aborting");
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
		{
			ft_printf("21sh :Can't open file\n");
			return (-1);
		}
	}
	return (fd);
}

static int	normal(int x, t_parser *parser, int i)
{
	int fd;

	if ((fd = open(parser[x].output.meta[i].name, O_WRONLY |
		O_TRUNC, 0777)) == -1)
	{
		ft_printf("21sh :Can't open file\n");
		return (-1);
	}
	close(fd);
	if ((fd = open(parser[x].output.meta[i].name, O_RDWR, 0777)) == -1)
	{
		ft_printf("21sh :Can't open file\n");
		return (-1);
	}
	return (fd);
}

static int	sinon(int x, t_parser *parser, int i)
{
	int fd;
	int stock;

	stock = 0;
	if (parser[x].output.meta[i].double_chevron)
	{
		if ((fd = is_d_chevron(x, parser, i)) == -1)
			return (-1);
	}
	else if ((fd = open(parser[x].output.meta[i].name,
		O_RDWR | O_CREAT | O_EXCL, 0777)) == -1)
	{
		if ((fd = normal(x, parser, i)) == -1)
			return (-1);
	}
	ft_easy_output(&stock, x, i, parser);
	if (dup2(fd, stock) == -1)
		ft_perror("dup", "Dup failed. Aborting");
	return (1);
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
			{
				if ((sinon(x, parser, i)) == -1)
					return (0);
			}
			if (parser[x].output.meta[i].next_exist == 0)
				break ;
			i++;
		}
	}
	return (check_dup_input(parser, x));
}
