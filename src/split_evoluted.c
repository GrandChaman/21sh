#include "ft_sh.h"

int		ft_isatoken(char c)
{
	if (c == ';')
		return (1);
	return (0);
}

char	checkquote(int *i, int *o, char *original) //si un ' dans des "" ...
{													// + effet de ces quotes genre '' ?
	char tableau[4] = "\"'`";
	int var;
	int stock;

	var = 0;
	while (tableau[var])
	{
		if (original[*i] == tableau[var])
		{
			stock = checkquote2(i, o, original, tableau[var]);
			if (stock == 0)
				return ('k');
			if (stock == -1)
			{
				printf("Here\n");
				return (tableau[var]);
			}
		}
		var++;
	}
	return ('n');
}

int		checkquote2(int *i, int *o, char *original, char c)
{
	if (original[*i] && original[*i] == c)
	{
		*i = *i + 1;
		while (original[*i] && original[*i] != c)
		{
			*i = *i + 1;
			*o = *o + 1;
		}
		if (original[*i] == '\0' && original[*i] != c)
			return (-1);
		*i = *i + 1;
		return (0) ;
	}
	return (1);
}

void	split_evoluted(char *original, char *ptr_need_quote)
{
	int i;
	int o;
	int z;
	int b;
	int isafile;
	char stock;

	isafile = 0;
	b = 0;
	z = 0;
	o = 0;
	i = 0;
	printf("original = %s\n", original);
	while (original[i])
	{
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		if (ft_isatoken(original[i]))
		{
			printf("Unexpected token %c\n", original[i]);
			return ;
		}
		while (original[i] && original[i] != ';')
		{
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0')
				break;
			while ((original[i] != ' ' && original[i] != '\t' && original[i] != ';') && original[i])
			{
				if (original[i] && original[i] == '<')
				{
					i++;
					isafile++;
				}
				while ((original[i] == ' ' || original[i] == '\t') && original[i])
					i++;
				stock = checkquote(&i, &o, original);
				if (stock == 'k')
					break;
				else if (stock > '\0' && stock != 'n')
				{
					printf("Manque une quote %c ", stock);
					*ptr_need_quote = stock;
					return ;
				}
				i++;
				o++;
			}
			if (original[i] == ';')
				break ;
			if (isafile)
			{
				isafile = 0;
				printf("commande [%d] file[%d] = %d\n", b, z, o);
			}
			else
				printf("commande [%d] mot[%d] = %d\n", b, z, o);
			o = 0;
			z++;
		}
		if (original[i] == '\0')
			break ;
		i++;
		if (ft_isatoken(original[i]))
		{
			printf("Unexpected token %c\n", original[i]);
			return ;
		}
		b++;
	}
}