/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:40:22 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/22 13:07:51 by fle-roy          ###   ########.fr       */
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

int			launch(char **args, t_list **head, t_bin_hash_table *ht,
	t_parser parser)
{
	pid_t		pid;
	int			status;
	t_bin_hash	*bin;
	char		**env;

	status = 0;
	bin = NULL;
	if (!ft_strchr(args[0], '/'))
		bin = get_elem_from_ht(ht, args[0]);
	if (check_if_can_exec(bin, args[0]))
		return (0);
	env = list_tochar2d(*head);
	pid = fork();
	if (pid == 0)
	{
		execve((bin ? bin->path : args[0]), &args[0], env);
		ft_printf("21sh: %s: execve failed.\n", args[0]);
		exit(-1);
	}
	else if (pid < 0)
		ft_putendl("21sh: fork error\n");
	else if (!parser.output.pipe)
		waitpid(pid, &status, WUNTRACED);
	ft_free2d((void **)env);
	return (status);
}
