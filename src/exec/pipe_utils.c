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

void		init_pipe_in_parent(t_parser *parser, t_dup *dup_el)
{
	if (parser->input.pipe && parser->output.pipe)
		dup_el->save_read = dup(dup_el->mpipe[0]);
	if ((parser->input.pipe && parser->output.pipe) ||
		(!parser->input.pipe && parser->output.pipe))
		pipe(dup_el->mpipe);
}

void		open_fds_in_fork(t_parser *parser, t_dup *dup_el)
{
	if (!(parser->input.pipe) && parser->output.pipe) //debut
		{
			close(dup_el->mpipe[0]);
			dup2(dup_el->mpipe[1], 1);
			close(dup_el->mpipe[1]);
		}
		else if (!(parser->output.pipe) && parser->input.pipe) //fin
		{
			close(dup_el->mpipe[1]);
			dup2(dup_el->mpipe[0], 0);
			close(dup_el->mpipe[0]);
		}
		else if (parser->input.pipe && parser->output.pipe) //sandwitch
		{
			dup2(dup_el->save_read, 0);
			dup2(dup_el->mpipe[1], 1);
			close(dup_el->save_read);
			close(dup_el->mpipe[1]);
		}
}

void		close_fds_in_parent(t_parser *parser, t_dup *dup_el)
{
	if (parser->input.pipe && parser->output.pipe) //sandwitch
	{
		close(dup_el->save_read);
		close(dup_el->mpipe[1]);
	}
	else if (!(parser->input.pipe) && parser->output.pipe) //debut
	{
		close(dup_el->mpipe[1]);
	}
	else if (!(parser->output.pipe) && parser->input.pipe) //fin
	{
		close(dup_el->mpipe[0]);
	}
}