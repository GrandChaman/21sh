#include "ft_sh.h"

void	init_parser(t_parser *parser, int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		parser[i].nb = nb;
		parser[i].cmd = NULL;
		parser[i].close_stdin = 0;
		parser[i].close_stdout = 0;
		parser[i].close_stderr = 0;
		parser[i].input.pipe = 0;
		parser[i].input.meta = NULL; // a initialiser plus tard
		parser[i].output.pipe = 0;
		parser[i].output.meta = NULL; // a initialiser plus tard
		i++;
	}
}

void	free_parser(t_parser *parser)
{
	int i;
	int nb;
	int o;

	i = 0;
	nb = 0;
	if (parser != NULL)
	{
		if (nb == 0)
			nb = parser[0].nb;
		while (i < nb)
		{
			o = 0;
			if (parser[i].cmd)
			{
				while (parser[i].cmd[o])
				{
					free(parser[i].cmd[o]);
					o++;
				}
				free(parser[i].cmd);
			}
			if (parser[i].input.meta)
			{
				o = 0;
				while (parser[i].input.meta)
				{
					free(parser[i].input.meta[o].name);
					if (parser[i].input.meta[o].next_exist == 0)
						break ;
					o++;
				}
			}
			if (parser[i].output.meta)
			{
				o = 0;
				while (parser[i].output.meta)
				{
					free(parser[i].output.meta[o].name);
					if (parser[i].output.meta[o].next_exist == 0)
						break ;
					o++;
				}
			}
			i++;
		}
		free(parser);
		parser = NULL;
	}
}

void	print_parser(t_parser *parser, int nb)
{
	int i;
	int o;

	o = 0;
	i = 0;
	while (i < nb)
	{
		ft_putendl("");
		if (parser[i].cmd != NULL)
		{
			o = 0;
			while (parser[i].cmd[o] != NULL)
			{
				ft_printf("parser[%d].cmd[%d] = %s\n", i, o, parser[i].cmd[o]);
				o++;
			}
		}
		printf("\nparser[%d].close_stdin = %d\n", i, parser[i].close_stdin);
		printf("parser[%d].close_stdout = %d\n", i, parser[i].close_stdout);
		printf("parser[%d].close_stderr = %d\n\n", i, parser[i].close_stderr);

		printf("parser[%d].input.pipe = %d\n\n", i, parser[i].input.pipe);

		if (parser[i].input.meta)
		{
			o = 0;
			while (parser[i].input.meta)
			{
				printf("parser[%d].input.meta[%d].name = %s\n", i, o, parser[i].input.meta[o].name);
				printf("parser[%d].input.meta[%d].stdin = %d\n", i, o, parser[i].input.meta[o].stdin);
				printf("parser[%d].input.meta[%d].stdout = %d\n", i, o, parser[i].input.meta[o].stdout);
				printf("parser[%d].input.meta[%d].stderr = %d\n\n", i, o, parser[i].input.meta[o].stderr);
				if (parser[i].input.meta[o].next_exist == 0)
					break;
				o++;
			}
		}
		printf("parser[%d].output.pipe = %d\n", i, parser[i].output.pipe);
		if (parser[i].output.meta)
		{
			o = 0;
			while (parser[i].output.meta)
			{
				printf("parser[%d].output.meta[%d].name = %s\n", i, o, parser[i].output.meta[o].name);
				printf("parser[%d].output.meta[%d].stdin = %d\n", i, o, parser[i].output.meta[o].stdin);
				printf("parser[%d].output.meta[%d].stdout = %d\n", i, o, parser[i].output.meta[o].stdout);
				printf("parser[%d].output.meta[%d].stderr = %d\n", i, o, parser[i].output.meta[o].stderr);
				printf("parser[%d].output.meta[%d].double_chevron = %d\n\n", i, o, parser[i].output.meta[o].double_chevron);
				if (parser[i].output.meta[o].next_exist == 0)
					break;
				o++;
			}
		}
		i++;
	}
}
