/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:40:09 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/27 16:33:42 by bluff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			chained_waited(t_list **wl)
{
	t_wait_el	*el;
	t_list		*tmp;
	int			status;

	if (!wl || !*wl)
		return (0);
	tmp = *wl;
	status = 1;
	while (tmp)
	{
		el = (t_wait_el*)tmp->content;
		tmp = tmp->next;
		if (!el)
			continue;
		waitpid(el->pid, &status, WUNTRACED);
	}
	ft_lstdel(wl, NULL);
	return (status);
}

static void	main_routine_2(t_list **head, t_var_m *m, int *status)
{
	t_wait_el	el;
	t_list		*wait_list;

	wait_list = NULL;
	m->nb = m->parser[0].nb;
	m->x = 0;
	while (m->x < m->nb)
	{
		el = execute(m->parser[m->x], head,
			&m->should_exit, m->shell->ht);
		if (el.pid < 0)
			break ;
		el.is_piped = m->parser[m->x].output.pipe | m->parser[m->x].input.pipe;
		if (el.pid > 0 && el.is_piped)
			ft_lstpush_front(&wait_list, &el, sizeof(t_wait_el));
		else if (el.pid > 0 && !el.is_piped)
			ft_lstpush_back(&wait_list, &el, sizeof(t_wait_el));
		if (!el.is_piped)
			*status = chained_waited(&wait_list);
		if (m->should_exit)
			break ;
		m->x++;
	}
	if (el.is_piped)
		*status = chained_waited(&wait_list);
}

void		main_routine(t_list **head, int status)
{
	t_var_m		ms;

	ms.fb = 0;
	ms.shell = get_ft_shell();
	ms.should_exit = 0;
	while (!ms.should_exit)
	{
		ms.parser = NULL;
		ms.cmd = read_command(NULL, status, 0, (!ms.fb ? ms.fb++ : ms.fb));
		if (!ms.cmd)
			return ;
		add_to_history(ms.shell, ms.cmd);
		if ((ms.cmd && ms.cmd[0] == '\0') ||
			!((ms.parser = get_parser(ms.cmd))))
		{
			ms.fb = 0;
			free(ms.cmd);
			continue ;
		}
		main_routine_2(head, &ms, &status);
		free_parser(ms.parser);
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
	print_ascii_art();
	main_routine(&env_lst, 0);
	cli_loader(1);
	free_hash_table(&shell->ht);
	ft_lstdel(&env_lst, free_env_var);
	free(shell->select);
	return (0);
}
