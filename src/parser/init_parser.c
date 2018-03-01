#include "ft_sh.h"

void	init_parser(t_parser *parser, int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		parser[i].nb_cmd = nb;
		parser[i].name_cmd = NULL;
		parser[i].argument = NULL;
		parser[i].input.exist = 0;
		parser[i].input.pipe = 0;
		parser[i].input.name_file = NULL;
		parser[i].output.standart = 0;
		parser[i].output.erreur = 0;
		parser[i].output.to_next_cmd = 0;
		parser[i].output.double_chevron = 0;
		parser[i].output.name_file = NULL;
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
			nb = parser[0].nb_cmd;
		while (i < nb)
		{
			o = 0;
			free(parser[i].name_cmd);
			if (parser[i].argument)
			{
				while (parser[i].argument[o])
				{
					free(parser[i].argument[o]);
					o++;
				}
			}
			if (parser[i].input.name_file)
				free(parser[i].input.name_file);
			if (parser[i].output.name_file)
				free(parser[i].output.name_file);
			i++;
		}
	}
}

void	print_parser(t_parser *parser, int nb)
{
	int i;
	int o;

	o = 0;
	i = 0;
	printf("\n\n	Structure du parser		\n\n");
	while (i < nb)
	{
		printf("\nparser[%d].name_cmd = %s\n", i, parser[i].name_cmd);
		if (parser[i].argument != NULL)
		{
			o = 0;
			while (parser[i].argument[o] != '\0')
			{
				printf("parser[%d].argument[%d] = %s\n", i, o, parser[i].argument[o]);
				o++;
			}
		}
		else
			printf("Pas d argument\n");
		printf("\nparser[%d].input.exist = %d\n", i, parser[i].input.exist);
		printf("parser[%d].input.pipe = %d\n", i, parser[i].input.pipe);
		printf("parser[%d].input.name_file = %s\n\n", i, parser[i].input.name_file);

		printf("parser[%d].output.standart = %d\n", i, parser[i].output.standart);
		printf("parser[%d].output.erreur = %d\n", i, parser[i].output.erreur);
		printf("parser[%d].output.to_next_cmd = %d\n", i, parser[i].output.to_next_cmd);
		printf("parser[%d].output.double_chevron = %d\n", i, parser[i].output.double_chevron);
		printf("parser[%d].output.name_file = %s\n", i, parser[i].output.name_file);
		i++;
	}
}
