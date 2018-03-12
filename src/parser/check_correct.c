#include "parser.h"

char	*check_correct(char *original) //Pour francis complet
{
	int			stock;
	char		*prompt;

	stock = is_correct(original); // a modifier pour le rendre bavard pour les fails
	if (stock < 0)
	{
		if (stock == -1) //double quote
			prompt = "d-quotes>";
		if (stock == -2) //simple quote
			prompt = "s-quotes>";
		if (stock == -3) //commande (pipe)
			prompt = "commands>";
		return (prompt);
	}
	if (stock == 0)
	{
//		ft_printf("\nFails\n");
		return (NULL);
	}
	if (stock == 1)
	{
		//ft_printf( ok ) !
		return (NULL);
	}
	return (NULL);
}
