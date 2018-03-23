/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:34:03 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/23 11:41:29 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	check_pipe(t_parser *parser)
{
	static int	mpipe[2];
	int			save_read_fd;

	if (parser->input.pipe && parser->output.pipe)
		save_read_fd = dup(mpipe[0]);
	if ((parser->input.pipe && parser->output.pipe) ||
		(!parser->input.pipe && parser->output.pipe))
		pipe(mpipe);
	if (!(parser->input.pipe) && parser->output.pipe) //debut
	{
		if (close(mpipe[0]) < 0)
			ft_perror("close", "system call failed.");
		dup2(mpipe[1], 1);
		if (close(mpipe[1]) < 0)
			ft_perror("close", "system call failed.");
	}
	else if (!(parser->output.pipe) && parser->input.pipe) //fin
	{
		if (close(mpipe[1]) < 0)
			ft_perror("close", "system call failed.");
		dup2(mpipe[0], 0);
		close(mpipe[0]);
	}
	else if (parser->input.pipe && parser->output.pipe) //sandwitch
	{
		dup2(save_read_fd, 0);
		dup2(mpipe[1], 1);
		if (close(save_read_fd) < 0)
			ft_perror("close", "system call failed.");
		if (close(mpipe[1]) < 0)
			ft_perror("close", "system call failed.");
	}
}
