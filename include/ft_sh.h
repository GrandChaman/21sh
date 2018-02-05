/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:56:03 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/05 18:09:00 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H
# include "libft.h"
# include <stdlib.h>
# include <term.h>
# include <unistd.h>
# define T_ESCAPE 27
# define T_ENTER 10
# define T_TAB 9
# define T_BACKSPACE 127
# define T_DELETE 2117294875
# define T_END 4610843
# define T_HOME 4741915
# define T_LARR 4479771
# define T_RARR 4414235
# define T_BARR 4348699
# define T_TARR 4243163
# define T_SLARR 74982532143899
# define T_SRARR 73883020516123
# define T_SBARR 72783508888347
# define T_STARR 71683997260571
# define ANSI_COLOR_B_RED      "\x1b[1;31m"
# define ANSI_COLOR_B_GREEN    "\x1b[1;32m"
# define TC_MOVELEFT "le"
# define TC_MOVERIGHT "nd"
# define TC_DELETE "dc"
# define TC_NDELETE "DC"
# define TC_MOVENLEFT "LE"
# define TC_INSERTNCHAR "IC"
# define TC_GOTONEXTLINE "nw"
# define TC_SAVECURPOS "sc"
# define TC_RESETCURPOS "rc"
# define TC_MOVEDOWN "do"
# define TC_MOVEUP "up"
# define TC_MOVENRIGHT "RI"

typedef struct			s_ft_sh
{
	t_list				*env;
	unsigned int		x_size;
	unsigned int		y_size;
	unsigned int		prompt_size;
	t_dbuf				buf;
	unsigned int		cursor;
	int					debug_tty;
}						t_ft_sh;

typedef	struct			s_ft_touch
{
	unsigned long		touch;
	void				(*f)(unsigned long);
}						t_ft_touch;

t_ft_sh	*get_ft_shell(void);
int		is_env_correct(void);
char		*ft_getcwd(void);
int		print_error(const char *title, const char *message);
void			apply_terminal_setting(int def);
int				display_prompt(int last_result);
char		*read_command(void);
void			exec_term_command(const char *code);
void			exec_term_command_p(const char *code, int p1, int p2);
void		spt_backspace(unsigned long touch);
void		spt_arrow(unsigned long touch);
void	get_screen_size(void);
int		ft_nputstr(char *str, int n);
void		spt_delete(unsigned long touch);
void		move_in_terminal(unsigned int touch, int should_update_buf);
void		backspace_command(void);

static t_ft_touch		g_ft_touch_list[] =
{
	{T_ESCAPE, spt_backspace},
	{T_TAB, NULL},
	{T_BACKSPACE, spt_backspace},
	{T_DELETE, spt_delete},
	{T_END, NULL},
	{T_HOME, NULL},
	{T_LARR, spt_arrow},
	{T_RARR, spt_arrow},
	{T_BARR, NULL},
	{T_TARR, NULL},
	{T_SLARR, NULL},
	{T_SRARR, NULL},
	{T_SBARR, NULL},
	{T_STARR, NULL}
};

#endif
