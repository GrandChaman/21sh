/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:33:45 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/23 19:18:49 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	is_fd(t_parser parser, int i, int stderr_fd)
{
	int stock;

	stock = 0;
	if (!(parser.output.meta[i].name[1] &&
		parser.output.meta[i].name[1] == '-'))
	{
		ft_easy_output(&stock, i, parser);
		if (parser.output.meta[i].name[1])
		{
			if (dup2(parser.output.meta[i].name[1] - '0', stock) == -1)
			{
				ft_fprintf(stderr_fd, "21sh: dup: dup failed\n");
				exit(-1);
			}
		}
		else
		{
			if (dup2(1, stock) == -1)
			{
				ft_fprintf(stderr_fd, "21sh: dup: dup failed\n");
				exit(-1);
			}
		}
	}
}

static int	is_d_chevron(t_parser parser, int i, int stderr_fd)
{
	int fd;

	if ((fd = open(parser.output.meta[i].name, O_RDWR | O_CREAT
		| O_EXCL | O_APPEND, 0777)) == -1)
	{
		if ((fd = open(parser.output.meta[i].name,
			O_RDWR | O_APPEND, 0777)) == -1)
		{
			ft_fprintf(stderr_fd, "21sh: Can't open file\n");
			return (-1);
		}
	}
	return (fd);
}

static int	normal(t_parser parser, int i, int stderr_fd)
{
	int fd;

	if ((fd = open(parser.output.meta[i].name, O_WRONLY |
		O_TRUNC, 0777)) == -1)
	{
		ft_fprintf(stderr_fd, "21sh: Can't open file\n");
		return (-1);
	}
	close(fd);
	if ((fd = open(parser.output.meta[i].name, O_RDWR, 0777)) == -1)
	{
		ft_fprintf(stderr_fd, "21sh: Can't open file\n");
		return (-1);
	}
	return (fd);
}

static int	sinon(t_parser parser, int i, int stderr_fd)
{
	int fd;
	int stock;

	stock = 0;
	if (parser.output.meta[i].double_chevron)
	{
		if ((fd = is_d_chevron(parser, i, stderr_fd)) == -1)
			return (-1);
	}
	else if ((fd = open(parser.output.meta[i].name,
		O_RDWR | O_CREAT | O_EXCL, 0777)) == -1)
	{
		if ((fd = normal(parser, i, stderr_fd)) == -1)
			return (-1);
	}
	ft_easy_output(&stock, i, parser);
	if (dup2(fd, stock) == -1)
	{
		ft_fprintf(stderr_fd, "21sh: dup: dup failed\n");
		exit(-1);
	}
	return (1);
}

int			check_dup(t_parser parser, int stderr_fd)
{
	int i;

	i = 0;
	if (parser.output.meta)
	{
		while (parser.output.meta)
		{
			if (parser.output.meta[i].name[0] == '&')
				is_fd(parser, i, stderr_fd);
			else
			{
				if ((sinon(parser, i, stderr_fd)) == -1)
					return (0);
			}
			if (parser.output.meta[i].next_exist == 0)
				break ;
			i++;
		}
	}
	return (check_dup_input(parser, stderr_fd));
}
