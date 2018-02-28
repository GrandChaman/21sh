<<<<<<< HEAD
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:40:09 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/27 18:04:02 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

>>>>>>> 66d1281a19597033a30d9c9939ef1cf0a65ffde9
#include "ft_sh.h"

int main(int argc, char **argv)
{
	//t_parser	*parser;
//	char		ptr_need_quote;
	
	if (argc == 3)
	{
		printf("tu te fout de ma geule\n");
		return (0);
	}
	if (argc == 1)
	{
		printf("ta oublier un truc\n");
		return (0);
	}
	check_correct(argv[1]);
	return (0);
}
									//refaire des exemple avec la structure finale
/*

	1 verifier que tt est bon avec les cotes...
	2 tout remplacer
	3 remplir structure

*/

<<<<<<< HEAD
/*
original = cat -e file | grep "ligne la" > other

parser[0].name_cmd = cat
parser[0].argument[0].name = -e
					  special = 0; (quote '' )
		  argument[1].name = file
		  			  special = 0;
parser[0].entree_cmd.
					exist = 0;
					pipe = 0;
					name_file = NULL;
parser[0].sortie_cmd.
					standart = 0;
					erreur = 0;
					to_next_cmd = 1;
					name_file = NULL;
					double_chevron = 0;
					continue_if_fail = 1;

parser[1].name_cmd = grep
parser[1].argument[0].name = ligne la
		  			  special = 0;
parser[1].entree_cmd.
					exist = 1;
					pipe = 1;
					name_file = NULL;
parser[1].sortie_cmd.
					standart = 0;
					erreur = 0;
					to_next_cmd = 0;
					name_file = other;
					double_chevron = 0;
					continue_if_fail = 1;

*/

/*
	original = ls > file && echo "lol"

parser[0].name_cmd = ls
parser[0].argument[0].name = file
		  			  special = 0;
parser[0].entree_cmd.
					exist = 1;
					pipe = 0;
					name_file = file;
parser[0].sortie_cmd.
					standart = 1;
					erreur = 0;
					to_next_cmd = 0;
					name_file = NULL;
					double_chevron = 0;
					continue_if_fail = 0;

parser[1].name_cmd = echo
parser[1].argument[0].name = lol
		  			  special = 0;
parser[1].entree_cmd.
					exist = 0;
					pipe = 0;
					name_file = NULL;
parser[1].sortie_cmd.
					standart = 1;
					erreur = 0;
					to_next_cmd = 0;
					name_file = NULL;
					double_chevron = 0;
					continue_if_fail = 1;
*/

/*

original = echo  "  file" >> file

parser[0].name_cmd = cat
parser[0].argument[0].name =   file
		  			  special = 0;
parser[0].entree_cmd.
					exist = 0;
parser[0].sortie_cmd.
					standart = 0;
					erreur = 0;
					to_next_cmd = 1;
					name_file = file;
					double_chevron = 1;
					continue_if_fail = 1;
*/

/*

original = cat *.c
parser[0].name_cmd = cat
parser[0].argument[0].name = *.c
		  			  special = 1;
parser[0].entree_cmd.
					exist = 0;
parser[0].sortie_cmd.
					standart = 1;
					erreur = 0;
					to_next_cmd = 1;
					name_file = NULL;
					double_chevron = 0;
					continue_if_fail = 1;

*/
=======
	shell = get_ft_shell();
	shell->is_a_tty = isatty(0);
	if (shell->is_a_tty)
	{
		apply_terminal_setting(0);
		get_screen_size();
	}
	ft_fprintf(shell->debug_tty, "YAY\n");
	cmd = read_command(NULL, NULL);
	ft_fprintf(shell->debug_tty, "YAY\n");
	ft_printf("%s%s\n", (!shell->is_a_tty ? "" : "\nTyped : "),cmd);
	free(cmd);
	if (shell->is_a_tty)
		apply_terminal_setting(1);
}

int		main(int argc, const char **argv, const char **environ)
{
	t_ft_sh *shell;

	(void)environ;
	shell = get_ft_shell();
	shell->debug_tty = -1;
	dbuf_init(&shell->buf);
	if (argc == 3 && !ft_strcmp("-d", argv[1]))
		init_debug(shell, argv[2]);
	if (!is_env_correct())
		return (1);
	main_routine();
	if (shell->debug_tty > 0)
		close(shell->debug_tty);
	free(shell->select);
	return (0);
}
>>>>>>> 66d1281a19597033a30d9c9939ef1cf0a65ffde9
