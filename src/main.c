/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:40:09 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/22 20:16:17 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_ft_sh		*get_ft_shell(void)
{
	static t_ft_sh shell;

	return (&shell);
}

static void	main_routine_2(t_list **head, int *status, t_var_m *ms)
{
	ms->nb = ms->parser[0].nb;
	ms->x = 0;
	while (ms->x < ms->nb)
	{
		check_pipe(ms->parser, ms->x, &ms->r_dup);
		if (!(check_dup(ms->parser, ms->x)))
		{
			*status = 1;
			break ;
		}
		*status = execute(ms->parser[ms->x], head,
			&ms->should_exit, ms->shell->ht);
		if (ms->should_exit)
			break ;
		init_dup(&ms->r_dup);
		ms->x++;
	}
}

void		main_routine(t_list **head, int status)
{
	t_var_m		ms;

	ms.fb = 0;
	init_r_dup(&ms.r_dup);
	ms.shell = get_ft_shell();
	ms.should_exit = 0;
	while (!ms.should_exit)
	{
		ms.parser = NULL;
		ms.cmd = read_command(NULL, status, 0, (!ms.fb ? ms.fb++ : ms.fb));
		add_to_history(ms.shell, ms.cmd);
		if ((ms.cmd && ms.cmd[0] == '\0') ||
			!((ms.parser = get_parser(ms.cmd))))
		{
			ms.fb = 0;
			free(ms.cmd);
			free_parser(ms.parser);
			ms.parser = NULL;
			continue ;
		}
		main_routine_2(head, &status, &ms);
		free_parser(ms.parser);
		//init_dup(&ms.r_dup); RIEN ???
		free(ms.cmd);
	}
}

static void	ignore_signal(int sig)
{
	(void)sig;
}

int			main(int argc, const char **argv, char **env)
{
	t_ft_sh *shell;
	t_list	*env_lst;

	argv = NULL;
	argc = 0;
	shell = get_ft_shell();
	env_lst = NULL;
	signal(SIGINT, ignore_signal);
	if (!is_env_correct())
		return (1);
	cli_loader(0);
	if (!shell->is_a_tty)
	{
		cli_loader(1);
		return (1);
	}
	char2d_tolist(&env_lst, env);
	shell->ht = load_bin_into_hash_table(env_lst);
	main_routine(&env_lst, 0);
	cli_loader(1);
	free_hash_table(&shell->ht);
	ft_lstdel(&env_lst, free_env_var);
	free(shell->select);
	return (0);
}
