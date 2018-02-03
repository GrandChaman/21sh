/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_settings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 13:37:56 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/03 15:26:46 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"
#include <sys/ioctl.h>

void	get_screen_size(void)
{
	struct winsize	w;
	t_ft_sh			*shell;

	shell = get_ft_shell();
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
	shell->x_size = w.ws_col;
	shell->y_size = w.ws_row;
}

static void		set_terminal_setting(struct termios *old, struct termios *new)
{
	*new = *old;
	new->c_lflag &= (~(ICANON | ECHO) | ISIG);
	new->c_cc[VMIN] = 1;
	new->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSAFLUSH, new))
	{
		free(old);
		print_error("tcsetattr", "system call failed.");
		exit(1);
	}
}

static struct termios	**retrieve_term_settings(void)
{
	static struct termios	*default_settings = NULL;

	return (&default_settings);
}

void			apply_terminal_setting(int def)
{
	struct termios			**default_settings;
	struct termios			new_settings;
	int						tmp;

	default_settings = retrieve_term_settings();
	if (*default_settings && def)
	{
		if ((tmp = tcsetattr(0, TCSANOW, *default_settings)))
			print_error("tcsetattr", "system call failed.");
		free(*default_settings);
		*default_settings = NULL;
		if (tmp)
			exit(1);
	}
	else
	{
		*default_settings = (struct termios*)ft_memalloc(
			sizeof(struct termios));
		if ((tmp = tcgetattr(0, *default_settings)))
		{
			free(*default_settings);
			exit(1);
		}
		set_terminal_setting(*default_settings, &new_settings);
	}
}
