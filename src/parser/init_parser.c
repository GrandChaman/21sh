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
		parser[i].entree_cmd.exist = 0;
		parser[i].entree_cmd.pipe = 0;
		parser[i].entree_cmd.name_file = NULL;
		parser[i].sortie_cmd.standart = 0;
		parser[i].sortie_cmd.erreur = 0;
		parser[i].sortie_cmd.to_next_cmd = 0;
		parser[i].sortie_cmd.double_chevron = 0;
		parser[i].sortie_cmd.name_file = NULL;
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
	if (parser[i].nb_cmd)
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
			if (parser[i].entree_cmd.name_file)
				free(parser[i].entree_cmd.name_file);
			if (parser[i].sortie_cmd.name_file)
				free(parser[i].sortie_cmd.name_file);
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
		printf("\nparser[%d].entree_cmd.exist = %d\n", i, parser[i].entree_cmd.exist);
		printf("parser[%d].entree_cmd.pipe = %d\n", i, parser[i].entree_cmd.pipe);
		printf("parser[%d].entree_cmd.name_file = %s\n\n", i, parser[i].entree_cmd.name_file);

		printf("parser[%d].sortie_cmd.standart = %d\n", i, parser[i].sortie_cmd.standart);
		printf("parser[%d].sortie_cmd.erreur = %d\n", i, parser[i].sortie_cmd.erreur);
		printf("parser[%d].sortie_cmd.to_next_cmd = %d\n", i, parser[i].sortie_cmd.to_next_cmd);
		printf("parser[%d].sortie_cmd.double_chevron = %d\n", i, parser[i].sortie_cmd.double_chevron);
		printf("parser[%d].sortie_cmd.name_file = %s\n", i, parser[i].sortie_cmd.name_file);
		i++;
	}
}