/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:56:03 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/16 15:42:52 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H
# include "libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <term.h>
# include <unistd.h>
# include <time.h>
# include <sys/param.h>
# include <fcntl.h>
# include <signal.h>
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
# define T_TARR 4283163
# define T_SLARR 74982532143899
# define T_SRARR 73883020516123
# define T_SBARR 72783508888347
# define T_STARR 71683997260571
# define T_ALT_LEFT 1146821403
# define T_ALT_RIGHT 1130044187
# define T_ALT_C 42947
# define T_ALT_V 10127586
# define T_ALT_X 8948194
# define T_CTRL_C 3
# define T_CTRL_D 4
# define T_CTRL_L 12
# define T_ALT_UP 1096489755
# define T_ALT_DOWN 1113266971
# define SHIFT_MASK 70584485632795
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
# define TC_MOVENUP "UP"
# define TC_MOVENDOWN "DO"
# define TC_MOVENRIGHT "RI"
# define TC_CARRIAGERETURN "cr"
# define TC_CLEAR_FROM_HERE "cd"
# define TC_REVERSEVIDEO "mr"
# define TC_RESETGRAPHICS "me"
# define TC_CLEAR "cl"
# define ABS(x) ((x) < 0 ? ((x) * -1) : (x))
# define SH_HIST_MAX_SIZE 10

typedef struct			s_ft_sh
{
	unsigned int		x_size;
	unsigned int		y_size;
	unsigned int		prompt_size;
	t_dbuf				buf;
	unsigned int		cursor;
	unsigned int		alt_cursor;
	unsigned int		select_start;
	int					select_size;
	char				*select;
	int					debug_tty;
	unsigned char		is_a_tty;
	t_list				*history;
	long				history_size;
	long				history_pos;
	char				*history_last;
	char				is_alt_shell;
	t_list				*autocomplete;
	t_list				*autocomplete_cusor;
	int					autocomplete_padding;
}						t_ft_sh;

typedef struct			s_ft_autoc_entry
{
	char				*name;
	char				*color;
	char				undeline;
	char				inverted;
	int					x_pos;
	int					y_pos;
}						t_ft_autoc_entry;

typedef	struct			s_ft_touch
{
	unsigned long		touch;
	void				(*f)(unsigned long);
}						t_ft_touch;

typedef	struct			s_ft_hist_entry
{
	char				*command;
	int					timestamp;
}						t_ft_hist_entry;

typedef	struct			s_input
{
	int					exist;
	int					pipe;
	char				*name_file;
}						t_input;

typedef	struct			s_output
{
	int					standart;
	int					erreur;
	int					to_next_cmd;
	char				*name_file;
	int					double_chevron;
	int					exist;
}						t_output;

typedef struct			s_cmd
{
	char				**name;
	int					special;
}						t_cmd;


typedef struct			s_parser
{
	char				**cmd;
	int					nb;
	t_input				input;
	t_output			output;
}						t_parser;

t_list					*ft_lstcopy(t_list **head);
void					ft_lstprint(t_list **head);
int						execute_env(char **args, t_list **head);
int						execute(t_parser parser, t_list **head, int *should_exit);
int						launch(char **args, t_list **head);
t_list					*create_list_from_env(char **env);
char					**create_env_from_list(t_list **head);
void					ft_lsterase(t_list **head);
void					ft_lstdelthis(t_list **head, char *str);
int						mini_cd(char **args, t_list **head);
int						mini_echo(char **args);
int						mini_env(char **args, t_list **head);
int						mini_exit(char **args);
char					*ft_getenv(t_list **head, char *elem);
char					*ft_path(t_list **head, char *cmd);
int						mini_help(char **args);
void					ft_lst_add_or_modify(int flag, t_list **head,
	char *name, char *value);
int						mini_setenv(char **args, t_list **head);
int						mini_unsetenv(char **args, t_list **head);
int						ft_problem_dir(char *arg);
int						too_many_args(char *cmd);

int				checkquote2_fill_intput(int *i, char *original, char c, t_parser *parser, int *b);
char			checkquote_fill_input(int *i, char *original, t_parser *parser, int *b);
int				redirections4(int *i, char *original);
int				checkquote2_fill_output(int *i, char *original, char c, t_parser *parser, int *b);
char			checkquote_fill_output(int *i, char *original, t_parser *parser, int *b);
int				checkquote2_fill_cmd(int *i, char *original, char c, t_parser *parser, int *b, int *j);
char			checkquote_fill_cmd(int *i, char *original, t_parser *parser, int *b, int *j);
void			free_parser(t_parser *parser);
t_parser		*get_parser(char *original);
char			*check_correct(char *original);
int				is_correct(char *original);
void			print_parser(t_parser *parser, int nb);
int				redirections3(int *i, char *original);
void			fill_parser(t_parser *parser, char *original);
int				ft_isatoken(char c);
int 			count_argv(int i, char *original);
int				count_cmd(char *original);
void			init_parser(t_parser *parser, int nb);
int				redirections2(int *i, char *original, t_parser *parser, int b);
int				count_argv(int i, char *original);
char			checkquote(int *i, int *o, char *original);
int				checkquote2(int *i, int *o, char *original, char c);
void			chevron(int *i, int *increment_something, char *original);
int				checkquote2(int *i, int *o, char *original, char c);
void			split_evoluted(t_parser *parser, char *original);

t_ft_sh					*get_ft_shell(void);
int						is_env_correct(void);
char					*ft_getcwd(void);
int						print_error(const char *title, const char *message);
void					apply_terminal_setting(int def);
int						display_prompt(int last_result);

char		*read_command(char *prompt, int status, int heredoc, int fb);
void			exec_term_command(const char *code);
void			exec_term_command_p(const char *code, int p1, int p2);
void		spt_arrow(unsigned long touch);
void		get_screen_size(int sig);
int		ft_nputstr(char *str, int n);
void		move_in_terminal(unsigned long touch, int should_update_buf);
void		backspace_command(unsigned long touch);
void		update_stdout(t_ft_sh *sh, int offset);
void		delete_command(unsigned long touch);
void (*get_special_char_f(unsigned long val))(unsigned long);
void		nav_touch_received(unsigned long touch);
void		move_select(unsigned long touch);
void		copy_select(unsigned long touch);
void		paste_select(unsigned long touch);
void		cut_select(unsigned long touch);
void		cli_loader(int destroy);
int 		load_history(t_ft_sh *sh, int unload);
void		add_to_history(t_ft_sh *sh, char *cmd);
int			is_alt_shell_begin(void);
unsigned int get_sh_cursor(void);
void		history_nav(unsigned long touch);
void	cli_reset_cursor(t_ft_sh *sh);
void			sh_clear_screen(unsigned long rchar);
void		vertical_nav(unsigned long touch);
void		collect_data(char *str_part);
void		ft_sh_autocomplete(unsigned long touch);
unsigned int			cursor_new_origin(t_ft_sh *sh);
void				delete_autocomplete_entry(void *el, size_t size);

static t_ft_touch		g_ft_touch_list[] =
{
	{T_TAB, ft_sh_autocomplete},
	{T_BACKSPACE, backspace_command},
	{T_DELETE, delete_command},
	{T_END, nav_touch_received},
	{T_HOME, nav_touch_received},
	{T_LARR, nav_touch_received},
	{T_RARR, nav_touch_received},
	{T_BARR, history_nav},
	{T_TARR, history_nav},
	{T_SLARR, nav_touch_received},
	{T_SRARR, nav_touch_received},
	{T_SBARR, nav_touch_received},
	{T_STARR, nav_touch_received},
	{T_ALT_LEFT, move_select},
	{T_ALT_RIGHT, move_select},
	{T_ALT_C, copy_select},
	{T_ALT_X, cut_select},
	{T_ALT_V, paste_select},
	{T_CTRL_L, sh_clear_screen},
	{T_ALT_UP, vertical_nav},
	{T_ALT_DOWN, vertical_nav},
	{0, NULL}
};

#endif
