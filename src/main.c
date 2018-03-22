/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:40:09 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/22 10:38:36 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_ft_sh	*get_ft_shell(void)
{
	static t_ft_sh shell;

	return (&shell);
}

void	init_debug(t_ft_sh *shell, const char *path)
{
	if ((shell->debug_tty = open(path, O_WRONLY)) < 0)
		return ;
	ft_fprintf(shell->debug_tty, "-------------------------------------\n");
}

void main_routine(t_list **head, int status)
{
	char		*cmd;
	t_ft_sh		*shell;
	t_parser	*parser;
	int			x;
	int 		nb;
	int			should_exit;
	t_dup		r_dup;
	int			fb;

	fb = 0;
	init_r_dup(&r_dup);
	shell = get_ft_shell();
	should_exit = 0;
	while (!should_exit)
	{
		cmd = read_command(NULL, status, 0, (!fb ? fb++ : fb));
		if (cmd && cmd[0] == '\0')
		{
			fb = 0;
			free(cmd);
			continue ;
		}
		add_to_history(shell, cmd);
		if ((parser = get_parser(cmd)))
		{
			nb = parser[0].nb;
			x = 0;
			while (x < nb)
			{
				check_pipe(parser, x, &r_dup);
				if (!(check_dup(parser, x)))
				{
					status = 1;
					break ;
				}
				status = execute(parser[x], head, &should_exit, shell->ht);
				if (should_exit)
					break;
				if (parser[x].close_stdout)
				{
					while ((parser[x].input.pipe || parser[x].output.pipe) && x < nb)
						x++;
				}
				init_dup(&r_dup);
				x++;
			}
			//ft_fprintf(shell->debug_tty, "YAY\n");
			free_parser(parser);
		}
		init_dup(&r_dup);
		free(cmd);
	}
}

static void ignore_signal(int sig)
{
	(void)sig;
}

int		main(int argc, const char **argv, char **env)
{
	t_ft_sh *shell;
	t_list	*env_lst;

	shell = get_ft_shell();
	signal(SIGINT, ignore_signal);
	shell->debug_tty = -1;
	if (argc == 3 && !ft_strcmp("-d", argv[1]))
		init_debug(shell, argv[2]);
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
	if (shell->debug_tty > 0)
		close(shell->debug_tty);
	free(shell->select);
	return (0);
}
