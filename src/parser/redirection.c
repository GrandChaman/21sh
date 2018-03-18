#include "ft_sh.h"

static void	there_is_space_space(int *i, char *original)
{
	while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
		*i = *i + 1;
}

static int	redirections3_2(int *i, char *original)
{
	if (original[*i] && original[*i] == '>')
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '>')
		{
			*i = *i + 1;
			there_is_space_space(i, original);
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (2);
		}
		else
		{
			if (original[*i] && original[*i + 1] && original[*i] == '&')
				if (!ft_isstd(original[*i + 1]) || (ft_isstd(original[*i + 1])
					&& (original[*i + 2] != ' ' && original[*i + 2] != '\0')))
					return (0);
			there_is_space_space(i, original);
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (2);
		}
	}
	return (1);
}

static int	double_chevron_2(int *i, char *original)
{
	*i = *i + 1;
	there_is_space_space(i, original);
	if (original[*i] == '\0' || ft_isatoken(original[*i]))
		return (0);
	while ((original[*i] != ' ' && original[*i] != '\t') && original[*i])
	{
		if (original[*i] == '\'' || original[*i] == '"')
			return (0);
		*i = *i + 1;
	}
	return (1);
}

static int	just_one_chevron(int *i, char *original)
{
	if (original[*i] && original[*i + 1] && original[*i] == '&')
	{
		if (!ft_isstd(original[*i + 1]) || (ft_isstd(original[*i + 1])
			&& (original[*i + 2] != ' ' && original[*i + 2] != '\0')))
			return (0);
	}
	there_is_space_space(i, original);
	if (original[*i] == '\0' || ft_isatoken(original[*i]))
		return (0);
	return (3);
}

int			redirections3(int *i, char *original)
{
	if (original[*i] && original[*i + 1] && (ft_isstd(original[*i])) &&
		(original[*i + 1] == '<' || original[*i + 1] == '>'))
	{
		if (original[*i - 1] != ' ')
			return (0);
		*i = *i + 1;
	}
	else if (*i != 0 && original[*i - 1] != ' ' && (original[*i] == '<' ||
		original[*i] == '>'))
		return (0);
	if (original[*i] && original[*i] == '<')
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '<')
			return (double_chevron_2(i, original));
		else
			return (just_one_chevron(i, original));
	}
	return (redirections3_2(i, original));
}