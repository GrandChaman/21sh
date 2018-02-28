#include "ft_sh.h"

char	*check_correct(char *str)
{
	int			stock;
	char		*prompt;

	stock = is_correct(str);
	if (stock < 0)
	{
		prompt = malloc(sizeof(char) * 10);
		if (stock == -1) //double quote
			prompt = "d-quotes>";
		if (stock == -2) //simple quote
			prompt = "s-quotes>";
		if (stock == -3) //commande (pipe)
			prompt = "commands>";
		if (stock == -4) //heredocs
			prompt = "here-doc>";
		//ta_fonction(prompt);
		//Faire un strjoint
//		printf("\nAppel a Francis !\n");
		return (prompt);
	}
	if (stock == 0)
	{
//		printf("\nFails\n");
		return (NULL);
	}
	if (stock == 1)
	{
//		printf("\nOK\n");
		return (NULL);
	}
	return (NULL);
}