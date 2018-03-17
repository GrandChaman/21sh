#include "ft_sh.h"

static void	is_space(int *i, char *original)
{
	while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
		*i = *i + 1;
}

int count_cmd(char *original)
{
	int i;
	int nb;
	int o;

	o = 0;
	nb = 0;
	i = 0;
	while (original[i])
	{
		is_space(&i, original);
		if (original[i] == '\0')
			return (nb);
		while ((original[i] != ' ' && original[i] != '\t') && original[i])
		{
			if (nb == 0)
				nb++;
			checkquote(&i, &o, original);
			if (original[i] == ';' || original[i] == '|')
			{
				i++;
				is_space(&i, original);
				if ((original[i] != ' ' && original[i] != '\t') && original[i])
					nb++;
			}
			i++;
		}
	}
	return (nb);
}

int count_redirection_output(int i, char *original)
{
	int nb;
	int o;

	o = 0;
	nb = 0;
	while (original[i])
	{
		is_space(&i, original);
		while ((original[i] != ' ' && original[i] != '\t') && original[i])
		{
			checkquote(&i, &o, original);
			is_space(&i, original);
			if (original[i] == '|' || original[i] == ';')
				return (nb);
			if (original[i] == '\0')
				break ;
			if (redirections_output(&i, original) != 1)
			{
				nb++;
				checkquote(&i, &o, original);			
			}
			if (original[i] == '|' || original[i] == ';')
				return (nb);
			i++;
		}
		is_space(&i, original);
		if (original[i] == '\0')
			break ;
		if (original[i] == '|' || original[i] == ';')
			return (nb);
	}
	return (nb);
}

int count_redirection_input(int i, char *original)
{
	int nb;
	int stock;
	int o;

	o = 0;
	nb = 0;
	while (original[i])
	{
		is_space(&i, original);
		while ((original[i] != ' ' && original[i] != '\t') && original[i])
		{
			checkquote(&i, &o, original);
			is_space(&i, original);
			if (original[i] == '|' || original[i] == ';')
				return (nb);
			if (original[i] == '\0')
				break ;
			stock = redirections_input(&i, original);
			if (stock != 1)
			{
				nb++;
				checkquote(&i, &o, original);			
			}
			if (original[i] == '|' || original[i] == ';')
				return (nb);
			i++;
		}
		is_space(&i, original);
		if (original[i] == '\0')
			break ;
		if (original[i] == '|' || original[i] == ';')
			return (nb);
	}
	return (nb);
}