/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:40:22 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/23 11:41:58 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	check_if_can_exec(t_bin_hash *bin, char *arg)
{
	if (!bin && !ft_strchr(arg, '/'))
		return (ft_printf("21sh: %s: No such command.\n", arg) && 1);
	if (!bin && ft_strchr(arg, '/') && access(arg, F_OK) == -1)
		return (ft_printf("21sh: %s: No such file.\n", arg) && 1);
	if ((bin && !bin->can_exec) || (!bin && access(arg, X_OK) == -1))
		return (ft_printf("21sh: %s: permission denied.\n", arg) && 1);
	return (0);
}

t_wait_el	launch(char **args, t_list **head, t_bin_hash_table *ht,
	t_parser parser)
{
	t_wait_el	el;
	int			status;
	t_bin_hash	*bin;
	char		**env;
	static int	mpipe[2];
	int			save_read_fd;
	
	status = 0;
	bin = NULL;
	el.pid = -1;
	if (!ft_strchr(args[0], '/'))
		bin = get_elem_from_ht(ht, args[0]);
	if (check_if_can_exec(bin, args[0]))
		return (el);
	env = list_tochar2d(*head);
	if (parser.input.pipe && parser.output.pipe)
		save_read_fd = dup(mpipe[0]);
	if ((parser.input.pipe && parser.output.pipe) ||
		(!parser.input.pipe && parser.output.pipe))
		pipe(mpipe);
	el.pid = fork();
	if (el.pid == 0)
	{
		if (!(parser.input.pipe) && parser.output.pipe) //debut
		{
			close(mpipe[0]);
			dup2(mpipe[1], 1);
			close(mpipe[1]);
		}
		else if (!(parser.output.pipe) && parser.input.pipe) //fin
		{
			close(mpipe[1]);
			dup2(mpipe[0], 0);
			close(mpipe[0]);
		}
		else if (parser.input.pipe && parser.output.pipe) //sandwitch
		{
			dup2(save_read_fd, 0);
			dup2(mpipe[1], 1);
			close(save_read_fd);
			close(mpipe[1]);
		}
		execve((bin ? bin->path : args[0]), &args[0], env);
		ft_printf("21sh: %s: execve failed.\n", args[0]);
		exit(-1);
	}
	else if (el.pid < 0)
		ft_putendl("21sh: fork error\n");
	if (parser.input.pipe && parser.output.pipe) //sandwitch
	{
		close(save_read_fd);
		close(mpipe[1]);
	}
	else if (!(parser.input.pipe) && parser.output.pipe) //debut
	{
		close(mpipe[1]);
	}
	else if (!(parser.output.pipe) && parser.input.pipe) //fin
	{
		close(mpipe[0]);
	}
	el.is_piped = parser.output.pipe;
	ft_free2d((void **)env);
	return (el);
}
