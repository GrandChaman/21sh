/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:40:22 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/21 16:23:16 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

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
	if (!bin && (!ft_strchr(args[0], '/') || access(args[0], X_OK) == -1))
		return (!ft_printf("21sh: %s: No such command.\n", args[0]));
	env = list_tochar2d(*head);
	pid = fork();
	if (pid == 0)
		return (execve((bin ? bin->path : args[0]), &args[0], env));
	else if (pid < 0)
		ft_putendl("21sh: fork error\n");
	else if (!parser.output.pipe)
		waitpid(pid, &status, WUNTRACED);
	ft_free2d((void **)env);
	return (status);
}
