/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:40:09 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/03 16:40:17 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_ft_sh	*get_ft_shell(void)
{
	static t_ft_sh shell;

	return (&shell);
}

int		main(int argc, const char **argv, const char **environ)
{
	dbuf_init(&get_ft_shell()->buf);
	(void)argc;
	(void)argv;
	(void)environ;
	if (!is_env_correct())
		return (1);
	apply_terminal_setting(0);
	display_prompt(0);
	char *res = read_command();
	ft_printf("\nTyped : %s\n", res);
	free(res);
	apply_terminal_setting(1);
	return (0);
}
