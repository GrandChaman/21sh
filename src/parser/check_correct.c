#include "ft_sh.h"

char	*check_correct(char *original) //Pour francis complet
{
	int			stock;
	char		*prompt;

	stock = is_correct(original);
	if (stock < 0)
	{
		if (stock == -1) //double quote
			prompt = "d-quotes>";
		if (stock == -2) //simple quote
			prompt = "s-quotes>";
		if (stock == -3) //commande (pipe)
			prompt = "commands>";
		if (stock == -4) //heredocs
			prompt = "here-docs>";
		return (prompt);
	}
	if (stock == 0)
	{
//		printf("\nFails\n");
		return (NULL);
	}
	if (stock == 1)
	{
		//printf( ok ) !
		return (NULL);
	}
	return (NULL);
}
