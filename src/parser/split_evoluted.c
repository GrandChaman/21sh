#include "ft_sh.h"

int		ft_isatoken(char c)
{
	if (c == ';' || c == '&' || c == '<' || c == '>')
		return (1);
	return (0);
}

int		split_evoluted(char *original, char *ptr_need_quote, t_parser *parser)
{
	int i;
	int o;
	int z;
	int b;
	int increment_something;
	int boite;
	char stock;
	int nbr_argv;

	increment_something = 0;
	b = 0;
	z = 0;
	o = 0;
	i = 0;
	printf("\noriginal = %s\n\n", original);
	while (original[i])
	{
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		if (ft_isatoken(original[i]))
		{
			printf("Unexpected token %c\n", original[i]);
			return (0);
		}
		nbr_argv = count_argv(i, original);
		printf("\nnbr_argv = %d\n", nbr_argv);
		while (original[i] && original[i] != ';' && original[i] != '|')
		{
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0')
				break;
			while ((original[i] != ' ' && original[i] != '\t' &&
			original[i] != ';' && original[i] != '|') && original[i])
			{
				boite = redirections2(&i, original, parser, b);
				if (boite == 0)
				{
					printf("Error de syntax\n");
					return (0);
				}
				while ((original[i] == ' ' || original[i] == '\t') && original[i])
					i++;
				stock = checkquote(&i, &o, original);
				if (stock == 'k')
					break;
				else if (stock > '\0' && stock != 'n')
				{
					printf("Manque une quote %c \n", stock);
					*ptr_need_quote = stock;
					return (-1);
				}
				i++;
				o++;
			}
			printf("Here o = %d et z = %d\n", o, z);
			if (z == 0)
			{
				if (!(parser[b].name_cmd = malloc(sizeof(char) * o)))
					return (0);
			}
			else
			{
				if (z == 1 && boite == 1)
					parser[b].argument = malloc(sizeof(char *) * nbr_argv + 1);
				if (boite == 1)
					parser[b].argument[z - 1] = malloc(sizeof(char) * o + 1);
				if (boite == 2)
					parser[b].sortie_cmd.name_file = malloc(sizeof(char) * o + 1);
				if (boite == 3)
					parser[b].entree_cmd.name_file = malloc(sizeof(char) * o + 1);
			}
			printf("la\n");
			printf("commande [%d] mot[%d] = %d\n", b, z, o);
			if (original[i] == '\0' || original[i] == ';' || original[i] == '|')
				break ;
			o = 0;
			z++;
		}
		z = 0;
		if (original[i] == '\0')
			break ;
		if (original[i] == '|')
		{
			printf("Ya un pipe\n"); //Faut un truc apres
			parser[b].sortie_cmd.to_next_cmd = 1;
			i++;
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0')
			{
				printf("faut une commande !\n");
				return (-1);
			}
			parser[b + 1].entree_cmd.pipe = 1; //Peux segfault
		}
		else
			i++;
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		if (original[i] && ft_isatoken(original[i]))
		{
			printf("Unexpected token %c\n", original[i]);
			return (0);
		}
		//Pas gere || et &&
		b++;
	}
	return (1);
}