#include "parser.h"

int		ft_isatoken(char c)
{
	if (c == ';' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int		ft_isstd(char c)
{
	if (c == '1' || c == '0' || c == '2')
		return (1);
	return (0);
}

void	init_var(t_vari *var)
{
	var->i_input = 0;
	var->i_output = 0;
	var->b = 0;
	var->z = 0;
	var->o = 0;
	var->i = 0;
	var->j = 0;
	var->box = 1;
	var->heredoc = 0;
}

void	fill_std_i(t_vari *var, t_parser *parser, char *original)
{
	if (ft_isstd(original[var->i - 1]))
	{
		if (original[var->i - 1] == '0')
			parser[var->b].input.meta[var->i_input].stdin = 1;
		else if (original[var->i - 1] == '1')
			parser[var->b].input.meta[var->i_input].stdout = 1;
		else if (original[var->i - 1] == '2')
			parser[var->b].input.meta[var->i_input].stderr = 1;
	}
	else
		parser[var->b].input.meta[var->i_input].stdin = 1;
}

void	fill_std_o(t_vari *var, t_parser *parser, char *original)
{
	if (ft_isstd(original[var->i - 1]))
	{
		if (original[var->i - 1] == '0')
			parser[var->b].output.meta[var->i_output].stdin = 1;
		else if (original[var->i - 1] == '1')
		{
			parser[var->b].output.meta[var->i_output].stdout = 1;
			parser[var->b].close_stdout = 1;
		}
		else if (original[var->i - 1] == '2')
		{
			parser[var->b].output.meta[var->i_output].stderr = 1;
			parser[var->b].close_stderr = 1;
		}
	}
	else
	{
		parser[var->b].output.meta[var->i_output].stdout = 1;
		parser[var->b].close_stdout = 1;
	}
}
