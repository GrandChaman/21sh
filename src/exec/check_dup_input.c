/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dup_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:16:10 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/23 19:18:57 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	is_fd(int i, t_parser parser, int stderr_fd, int stock)
{
	if (!(parser.input.meta[i].name[1] &&
		parser.input.meta[i].name[1] == '-'))
	{
		ft_easy_input(&stock, i, parser);
		if (parser.input.meta[i].name[1])
		{
			if ((dup2(stock, parser.input.meta[i].name[1] - 48)) == -1)
			{
				ft_fprintf(stderr_fd, "21sh: dup: dup failed\n");
				exit(-1);
			}
		}
		else if ((dup2(stock, 0)) == -1)
		{
			ft_fprintf(stderr_fd, "21sh: dup: dup failed\n");
			exit(-1);
		}
	}
	else if (parser.input.meta[i].name[1] &&
		parser.input.meta[i].name[1] == '-')
		ft_easy2(parser);
}

static void	is_heredoc_2(t_parser parser, int i, int stderr_fd)
{
	char	*str;
	char	*str2;
	int		fd;

	str = "/tmp/21sh_heredoc";
	str2 = ft_itoa(parser.input.meta[i].heredoc_number);
	str = ft_strjoin(str, str2);
	if ((fd = open(str, O_RDWR, 0777)) == -1)
	{
		ft_fprintf(stderr_fd, "21sh: Can't open heredoc file /tmp\n");
		exit(-1);
	}
	free(str);
	free(str2);
	if (dup2(fd, 0) == -1)
	{
		ft_fprintf(stderr_fd, "21sh: dup: dup failed\n");
		exit(-1);
	}
}

static int	is_normal(t_parser parser, int i, int stderr_fd)
{
	int fd;
	int stock;

	stock = 0;
	if ((fd = open(parser.input.meta[i].name, O_RDWR, 0777)) == -1)
	{
		ft_fprintf(stderr_fd, "21sh: no such file or directory\n");
		return (0);
	}
	ft_easy_input(&stock, i, parser);
	if (dup2(fd, stock) == -1)
	{
		ft_fprintf(stderr_fd, "21sh: dup: dup failed\n");
		exit(-1);
	}
	return (1);
}

int			check_dup_input(t_parser parser, int stderr_fd)
{
	int i;

	i = 0;
	if (parser.input.meta)
	{
		while (parser.input.meta)
		{
			if (parser.input.meta[i].name &&
				parser.input.meta[i].name[0] == '&')
				is_fd(i, parser, stderr_fd, 0);
			else
			{
				if (parser.input.meta[i].heredoc_number)
					is_heredoc_2(parser, i, stderr_fd);
				else if (!(is_normal(parser, i, stderr_fd)))
					return (0);
			}
			if (parser.input.meta[i].next_exist == 0)
				break ;
			i++;
		}
	}
	return (1);
}

void		ft_easy_input(int *stock, int i, t_parser parser)
{
	if (parser.input.meta[i].stdin)
		*stock = 0;
	else if (parser.input.meta[i].stdout)
		*stock = 1;
	else if (parser.input.meta[i].stderr)
		*stock = 2;
}
