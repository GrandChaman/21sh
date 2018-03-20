#ifndef PARSER_H
# define PARSER_H
# include "ft_sh.h"

typedef struct			s_meta_output
{
	char				*name;
	int					stdin;
	int 				stdout;
	int					stderr;
	int					double_chevron;
	int					next_exist;
}						t_meta_output;

typedef struct			s_meta_input
{
	int					heredoc_number;
	char				*name;
	int					stdin;
	int 				stdout;
	int					stderr;
	int					next_exist;
}						t_meta_input;

typedef	struct			s_input
{
	int					pipe;
	t_meta_input		*meta;
}						t_input;

typedef	struct			s_output
{
	int					pipe;
	t_meta_output		*meta;
}						t_output;

typedef struct			s_parser
{
	char				**cmd;
	int					nb;
	int					close_stdin;
	int					close_stdout;
	int					close_stderr;
	t_input				input;
	t_output			output;
}						t_parser;

typedef struct			s_vari
{
	int o;
	int z;
	int b;
	int nbr_argv;
	int j;
	char stock;
	int boite;
	int box;
	int nbr_redirection_input;
	int i_input;
	int nbr_redirection_output;
	int i_output;
	int i;
	int heredoc;
}						t_vari;

void	call_heredoc(t_vari var, char *ori);
void			fill_std_o(t_vari *var, t_parser *parser, char *ori);
void			fill_std_i(t_vari *var, t_parser *parser, char *ori);
void			init_var(t_vari *var);
int				ft_isstd(char c);
void			init_meta_output(t_parser *parser, int b, int nb);
void			init_meta_input(t_parser *parser, int b, int nb);
int				count_redirection_output(int i, char *ori);
int				redirections_output(int *i, char *ori);
int				count_redirection_input(int i, char *ori);
int				redirections_input(int *i, char *ori);
int				checkquote2_fill_intput(t_vari *var, char *ori, char c, t_parser *parser);
char			checkquote_fill_input(t_vari *var, char *ori, t_parser *parser);
int				redirections4(char *ori, t_parser *parser, t_vari *var);
int				checkquote2_fill_output(t_vari *var, char *ori, char c, t_parser *parser);
char			checkquote_fill_output(t_vari *var, char *ori, t_parser *parser);
int				checkquote2_fill_cmd(t_vari *var, char *ori, char c, t_parser *parser);
char			checkquote_fill_cmd(t_vari *var, char *ori, t_parser *parser);
void			free_parser(t_parser *parser);
t_parser		*get_parser(char *ori);
char			*check_correct(char *ori);
int				is_correct(char *ori);
int				is_correct_talk(char *ori);
void			print_parser(t_parser *parser, int nb);
int				redirections3(int *i, char *ori);
void			fill_parser(t_parser *parser, char *ori);
int				ft_isatoken(char c);
int 			count_argv(int i, char *ori);
int				count_cmd(char *ori);
void			init_parser(t_parser *parser, int nb);
int				redirections2(char *ori, t_vari *var);
int				count_argv(int i, char *ori);
char			checkquote(int *i, int *o, char *ori);
void			chevron(int *i, int *increment_something, char *ori);
int				checkquote2(int *i, int *o, char *ori, char c);
void			split_evoluted(t_parser *parser, char *ori);

#endif
