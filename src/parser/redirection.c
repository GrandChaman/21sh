#include "ft_sh.h"

int		redirections2(char *original, t_vari *var)
{
	if (original[var->i] && original[var->i + 1] && (ft_isstd(original[var->i])) &&
		(original[var->i + 1] == '<' || original[var->i + 1] == '>'))
		var->i++;
	if (original[var->i] && original[var->i] == '<') //a gere les erreurs
	{
		var->i++;
		if (original[var->i] && original[var->i] == '<')
		{
			var->i++;
			while ((original[var->i] == ' ' || original[var->i] == '\t') && original[var->i])
				var->i++;
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
		}
		else
		{
			while ((original[var->i] == ' ' || original[var->i] == '\t') && original[var->i])
				var->i++;
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
			return (3);
		}
	}
	if (original[var->i] && original[var->i] == '>')
	{
		var->i++;
		if (original[var->i] && original[var->i] == '>')
		{
			var->i++;
			while ((original[var->i] == ' ' || original[var->i] == '\t') && original[var->i])
				var->i++;
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
			return (2);
		}
		else
		{
			while ((original[var->i] == ' ' || original[var->i] == '\t') && original[var->i])
				var->i++;
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
			return (2);
		}
	}
	return (1);
}

int		redirections3(int *i, char *original)
{
	if (original[*i] && original[*i] == '<')
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '<')
		{
			*i = *i + 1;
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (-1);
		}
		else
		{
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (3);
		}
	}
	if (original[*i] && original[*i] == '>')
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '>')
		{
			*i = *i + 1;
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (2);
		}
		else
		{
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (2);
		}
	}
	return (1);
}

int		redirections4(char *original, t_parser *parser, t_vari *var)
{
	if (original[var->i] && original[var->i + 1] && (ft_isstd(original[var->i])) &&
			(original[var->i + 1] == '<' || original[var->i + 1] == '>'))
		var->i++;
	if (original[var->i] && original[var->i] == '<')
	{
		fill_std_i(var, parser, original);
		var->i++;
		if (original[var->i] && original[var->i] == '<')
		{
			var->i++;
			while ((original[var->i] == ' ' || original[var->i] == '\t') && original[var->i])
				var->i++;
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
			return (-1);
		}
		else
		{
			while ((original[var->i] == ' ' || original[var->i] == '\t') && original[var->i])
				var->i++;
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
			return (3);
		}
	}
	if (original[var->i] && original[var->i] == '>')
	{
		fill_std_o(var, parser, original);
		var->i++;
		if (original[var->i] && original[var->i] == '>')
		{
			var->i++;
			while ((original[var->i] == ' ' || original[var->i] == '\t') && original[var->i])
				var->i++;
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
				parser[var->b].output.meta[var->i_input].double_chevron = 1;	
			return (2);
		}
		else
		{
			while ((original[var->i] == ' ' || original[var->i] == '\t') && original[var->i])
				var->i++;
			if (original[var->i] == '\0' || ft_isatoken(original[var->i]))
				return (0);
			return (2);
		}
	}
	return (1);
}


int		redirections_input(int *i, char *original)
{
	if (original[*i] && original[*i] == '<') //a gere les erreurs
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '<')
		{
			*i = *i + 1;
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (-1);
		}
		else
		{
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (3);
		}
	}
	if (original[*i] && original[*i] == '>')
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '>')
		{
			*i = *i + 1;
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (1);
			return (1);
		}
		else
		{
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (1);
			return (1);
		}
	}
	return (1);
}

int		redirections_output(int *i, char *original)
{
	if (original[*i] && original[*i] == '<') //a gere les erreurs
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '<')
		{
			*i = *i + 1;
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (1);
			return (1);
		}
		else
		{
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (1);
			return (1);
		}
	}
	if (original[*i] && original[*i] == '>')
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '>')
		{
			*i = *i + 1;
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (2);
		}
		else
		{
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (2);
		}
	}
	return (1);
}