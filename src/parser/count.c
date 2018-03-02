#include "ft_sh.h"

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
			checkquote(&i, &o, original);
			stock = redirections3(&i, original);
			checkquote(&i, &o, original);
			if (stock != 1)
				nb = nb - 2;
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
		nb++;
	}
	return (nb);
}