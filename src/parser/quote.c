#include "ft_sh.h"

char	checkquote(int *i, int *o, char *original) // effet '' ?
{
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
	//			printf("Here\n");
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
