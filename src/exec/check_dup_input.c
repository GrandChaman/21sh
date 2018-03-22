/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dup_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:16:10 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 17:22:06 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	is_fd(int x, int i, t_parser *parser)
{
	int stock;

	stock = 0;
	if (!(parser[x].input.meta[i].name[1] &&
		parser[x].input.meta[i].name[1] == '-'))
	{
		ft_easy_input(&stock, x, i, parser);
		if (parser[x].input.meta[i].name[1])
		{
			if ((dup2(stock, parser[x].input.meta[i].name[1] - 48)) == -1)
				ft_perror("dup", "Dup failed. Aborting");
		}
		else
		{
			if ((dup2(stock, 0)) == -1)
				ft_perror("dup", "Dup failed. Aborting");
		}
	}
}

static void	is_heredoc_2(int x, t_parser *parser, int i)
{
	char	*str;
	char	*str2;
	int		fd;

	str = "/tmp/21sh_heredoc";
	str2 = ft_itoa(parser[x].input.meta[i].heredoc_number);
	str = ft_strjoin(str, str2);
	if ((fd = open(str, O_RDWR, 0777)) == -1)
		ft_perror("21sh","Can't open heredoc file /tmp");
	free(str);
	free(str2);
	if (dup2(fd, 0) == -1)
		ft_perror("dup", "Dup failed. Aborting");
}

static int	is_normal(int x, t_parser *parser, int i)
{
	int fd;
	int stock;

	stock = 0;
	if ((fd = open(parser[x].input.meta[i].name, O_RDWR, 0777)) == -1)
	{
		ft_printf("21sh :no such file or directory\n");
		return (0);
	}
	ft_easy_input(&stock, x, i, parser);
	if (dup2(fd, stock) == -1)
		ft_perror("dup", "Dup failed. Aborting");
	return (1);
}

int			check_dup_input(t_parser *parser, int x)
{
	int i;

	i = 0;
	if (parser[x].input.meta)
	{
		while (parser[x].input.meta)
		{
			if (parser[x].input.meta[i].name &&
				parser[x].input.meta[i].name[0] == '&')
				is_fd(x, i, parser);
			else
			{
				if (parser[x].input.meta[i].heredoc_number)
					is_heredoc_2(x, parser, i);
				else if (!(is_normal(x, parser, i)))
					return (0);
			}
			if (parser[x].input.meta[i].next_exist == 0)
				break ;
			i++;
		}
	}
	return (1);
}

void		ft_easy_input(int *stock, int x, int i, t_parser *parser)
{
	if (parser[x].input.meta[i].stdin)
		*stock = 0;
	else if (parser[x].input.meta[i].stdout)
		*stock = 1;
	else if (parser[x].input.meta[i].stderr)
		*stock = 2;
}
