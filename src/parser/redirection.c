#include "ft_sh.h"

int		redirections2(int *i, char *original, t_parser *parser, int b, int result)
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
	/*		if (result == 1)
				parser[b].output.double_chevron = 1;*/ // a modifier dans le futur, manque 1 valeur
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

int		redirections3(int *i, char *original)
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

int		redirections4(int *i, char *original)
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