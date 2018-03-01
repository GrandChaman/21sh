#include "ft_sh.h"

char	*check_correct(char *original)
{
	int			stock;
	char		*prompt;
	t_parser	*parser;

	stock = is_correct(original);
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
			prompt = "here-docs>";
		printf("\nAppel a Francis !\n");
		printf("prompt = %s\n", prompt);
		return (prompt);
	}
	if (stock == 0)
	{
		printf("\nFails\n");
		return (NULL);
	}
	if (stock == 1)
	{
		printf("\nOK\n");
		stock = count_cmd(original);
		parser = malloc(sizeof(t_parser) * stock);
		init_parser(parser, stock);
		if (!(split_evoluted(parser, original)))//malloc + mise en place des flags
			return (NULL);					//Faut quitter
		//print_parser(parser, stock);
		fill_parser(parser, original);       //remplissage des mallocs
		print_parser(parser, stock);
		return (NULL);
	}
	return (NULL);
}
