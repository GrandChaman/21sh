#include "parser.h"

t_parser	*get_parser(char *original) //Pour victor
{
	int			stock;
	t_parser	*parser;

	stock = is_correct(original);
	if (stock == 0)
	{
//		printf("\nFails\n");
		return (NULL);
	}
	if (stock < 0)
	{
		printf("Francis complet\n");
		return (NULL);
	}
	if (stock == 1)
	{
	//	printf("\nOK\n");
		stock = count_cmd(original);
	//	printf("------------------------------------------- nb commandes = %d\n",stock);
		parser = malloc(sizeof(t_parser) * stock);
		init_parser(parser, stock);
		split_evoluted(parser, original);
		fill_parser(parser, original);
	//	print_parser(parser, stock);
		return (parser);
	}
	return (NULL);
}