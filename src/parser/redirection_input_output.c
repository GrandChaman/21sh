#include "ft_sh.h"

static void	there_is_space_space(int *i, char *original)
{
	while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
		*i = *i + 1;
}

static int	redirections_input_2(int *i, char *original)
{
	if (original[*i] && original[*i] == '>')
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '>')
		{
			*i = *i + 1;
			there_is_space_space(i, original);
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (1);
			return (1);
		}
		else
		{
			there_is_space_space(i, original);
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (1);
			return (1);
		}
	}
	return (1);
}

int			redirections_input(int *i, char *original)
{
	if (original[*i] && original[*i] == '<')
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '<')
		{
			*i = *i + 1;
			there_is_space_space(i, original);
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (3);
		}
		else
		{
			there_is_space_space(i, original);
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (3);
		}
	}
	return (redirections_input_2(i, original));
}

static int	redirections_output_2(int *i, char *original)
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
			there_is_space_space(i, original);
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (2);
		}
	}
	return (1);
}

int			redirections_output(int *i, char *original)
{
	if (original[*i] && original[*i] == '<')
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '<')
		{
			*i = *i + 1;
			there_is_space_space(i, original);
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (1);
			return (1);
		}
		else
		{
			there_is_space_space(i, original);
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (1);
			return (1);
		}
	}
	return (redirections_output_2(i, original));
}