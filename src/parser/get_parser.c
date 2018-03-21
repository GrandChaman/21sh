#include "ft_sh.h"

t_parser	*get_parser(char *original)
{
	int			stock;
	t_parser	*parser;

	stock = is_correct_talk(original);
	if (stock == 0)
		return (NULL);
	if (stock < 0)
		return (NULL);
	if (stock == 1)
	{
		stock = count_cmd(original);
//		printf("------------------------------------------- nb commandes = %d\n", stock);
		if (!(parser = malloc(sizeof(t_parser) * stock)))
			exit(0);
		init_parser(parser, stock);
		split_evoluted(parser, original);
		fill_parser(parser, original);
		print_parser(parser, stock);
		return (parser);
	}
	return (NULL);
}