#include "ft_sh.h"

void	init_meta_input(t_parser *parser, int b, int nb)
{
	int o;

	o = 0;
	while (o < nb)
	{
		parser[b].input.meta[o].heredoc_number = 0;
		parser[b].input.meta[o].name = NULL;
		parser[b].input.meta[o].stdin = 0;
		parser[b].input.meta[o].stdout = 0;
		parser[b].input.meta[o].stderr = 0;
		parser[b].input.meta[o].next_exist = 1;
		o++;
	}
	parser[b].input.meta[o - 1].next_exist = 0;
}

void	init_meta_output(t_parser *parser, int b, int nb)
{
	int o;

	o = 0;
	while (o < nb)
	{
		parser[b].output.meta[o].name = NULL;
		parser[b].output.meta[o].stdin = 0;
		parser[b].output.meta[o].stdout = 0;
		parser[b].output.meta[o].stderr = 0;
		parser[b].output.meta[o].double_chevron = 0;
		parser[b].output.meta[o].next_exist = 1;
		o++;
	}
	parser[b].output.meta[o - 1].next_exist = 0;
}