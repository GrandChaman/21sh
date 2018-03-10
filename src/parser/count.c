#include "parser.h"

int	count_cmd(char *original)
{
	int i;
	int nb;
	int stock;
	int o;

	o = 0;
	nb = 0;
	i = 0;
	while (original[i])
	{
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		if (original[i] == '\0')
			return (nb);
		while ((original[i] != ' ' && original[i] != '\t') && original[i])
		{
			if (nb == 0)
				nb++;
			stock = checkquote(&i, &o, original);
			if (original[i] == ';' || original[i] == '|')
			{
				i++;
				while ((original[i] == ' ' || original[i] == '\t') && original[i])
					i++;
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
	int stock;
	int o;

	o = 0;
	nb = 0;
	while (original[i])
	{
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		while ((original[i] != ' ' && original[i] != '\t') && original[i])
		{
			checkquote(&i, &o, original);
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '|' || original[i] == ';')
				return (nb);
			if (original[i] == '\0')
			{
				break ;
			}
			stock = redirections_output(&i, original);
			if (stock != 1)
			{
				nb++;
				checkquote(&i, &o, original);			
			}
			if (original[i] == '|' || original[i] == ';')
				return (nb);
			i++;
		}
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
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
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		while ((original[i] != ' ' && original[i] != '\t') && original[i])
		{
			checkquote(&i, &o, original);
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '|' || original[i] == ';')
				return (nb);
			if (original[i] == '\0')
			{
				break ;
			}
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
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		if (original[i] == '\0')
			break ;
		if (original[i] == '|' || original[i] == ';')
			return (nb);
	}
	return (nb);
}

int count_argv(int i, char *original)
{
	int nb;
	int stock;
	int o;

	o = 0;
	nb = 0;
	while (original[i])
	{
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		while ((original[i] != ' ' && original[i] != '\t') && original[i])
		{
			while ((checkquote(&i, &o, original)) == 'k')
			{
				nb++;
				while ((original[i] == ' ' || original[i] == '\t') && original[i])
					i++;
			}
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '|' || original[i] == ';')
				break ;
			if (original[i] == '\0')
			{
				nb--;
				break ;
			}
			stock = redirections3(&i, original);
			if (stock != 1)
			{
				checkquote(&i, &o, original);
				nb = nb - 1;
			}
			if (original[i] == '|' || original[i] == ';')
				return (nb);
			i++;
		}
		nb++;
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		if (original[i] == '\0')
			break ;
		if (original[i] == '|' || original[i] == ';')
			return (nb);
	}
	return (nb);
}