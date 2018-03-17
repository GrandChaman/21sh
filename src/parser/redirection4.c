#include "ft_sh.h"

void		there_is_space(t_vari *var, char *original)
{
	while ((original[var->i] == ' ' || original[var->i] == '\t')
		&& original[var->i])
		var->i++;
}

static int	redirections4_2(t_vari *var, t_parser *parser, char *original)
{
	if (original[var->i] && original[var->i] == '>')
	{
		fill_std_o(var, parser, original);
		var->i++;
		if (original[var->i] && original[var->i] == '>')
		{
			var->i++;
			there_is_space(var, original);
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
			parser[var->b].output.meta[var->i_input].double_chevron = 1;
			return (2);
		}
		else
		{
			there_is_space(var, original);
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
			return (2);
		}
	}
	return (1);
}

static int	is_heredoc(char *original, t_parser *parser, t_vari *var)
{
	var->i++;
	there_is_space(var, original);
	if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
		return (0);
	var->heredoc++;
	parser[var->b].input.meta[var->i_input].heredoc_number = var->heredoc;
	call_heredoc(var, original);
	there_is_space(var, original);
	return (4);
}

int			redirections4(char *original, t_parser *parser, t_vari *var)
{
	if (original[var->i] && original[var->i + 1] && (ft_isstd(original[var->i]))
		&& (original[var->i + 1] == '<' || original[var->i + 1] == '>'))
		var->i++;
	if (original[var->i] && original[var->i] == '<')
	{
		fill_std_i(var, parser, original);
		var->i++;
		if (original[var->i] && original[var->i] == '<')
			return (is_heredoc(original, parser, var));
		else
		{
			there_is_space(var, original);
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
			return (3);
		}
	}
	return (redirections4_2(var, parser, original));
}