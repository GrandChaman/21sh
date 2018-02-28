#include "ft_sh.h"

void	init_parser(t_parser *parser, int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		parser[i].exist = 1;
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
	parser[i].exist = 0;
}

void	print_parser(t_parser *parser)
{
	int i;
	int o;

	o = 0;
	i = 0;
	printf("\n\n	Structure du parser		\n\n");
	while (parser[i].exist)
	{
		printf("\nparser[%d].name_cmd = %s\n", i, parser[i].name_cmd);
		o = 0;
		/*while (parser[i].argument[o])
		{
			printf("parser[%d].argument[%d] = %s\n", i, o, parser[i].argument[o]);
			o++;
		}*/
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