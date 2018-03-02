#include "ft_sh.h"

int		ft_isatoken(char c)
{
	if (c == ';' || c == '&' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

void	split_evoluted(t_parser *parser, char *original)
{
	int i;
	int o;
	int z;
	int b;
	int nbr_argv;
	int boite;
	int box;

	b = 0;
	z = 0;
	o = 0;
	i = 0;
	printf("\noriginal = %s\n\n", original);
	while (original[i])
	{
		box = 1;
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		nbr_argv = count_argv(i, original) + 2;
		while (original[i] && original[i] != ';' && original[i] != '|')
		{
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0')
				break;
			while ((original[i] != ' ' && original[i] != '\t' &&
			original[i] != ';' && original[i] != '|') && original[i])
			{
				checkquote(&i, &o, original);
				if (original[i] == '\0')
					break;
				boite = redirections2(&i, original, parser, b);
				if (boite != 1)
				{
					checkquote(&i, &o, original);
					box = boite;
					break ;
				}
				i++;
				o++;
			}
			printf("box = %d\n", box);
			if (z == 0 && box == 1)
			{
				printf("nombre de mot dans la commande = %d\n", nbr_argv);
				if (!(parser[b].cmd = malloc(sizeof(char *) * nbr_argv + 1)))
					exit(0);
			}
			if (box == 1)
			{
				printf("malloc parser[%d].cmd[%d] = %d\n", b, z, o);
				if (!(parser[b].cmd[z] = malloc(sizeof(char) * o + 1)))
					exit(0);
			}
			if (box == 2)
			{
				while ((original[i] != ' ' && original[i] != '\t' &&
				original[i] != ';' && original[i] != '|') && original[i])
				{
					i++;
					o++;
				}
				printf("malloc parser[%d].output.name_file = %d\n", b, o);
				if (!(parser[b].output.name_file = malloc(sizeof(char) * o + 1)))
					exit(0);
			}
			if (box == 3)
			{
				while ((original[i] != ' ' && original[i] != '\t' &&
				original[i] != ';' && original[i] != '|') && original[i])
				{
					i++;
					o++;
				}
				printf("malloc parser[%d].input.name_file = %d\n", b , o);
				if (!(parser[b].input.name_file = malloc(sizeof(char) * o + 1)))
					exit(0);
			}
			printf("commande [%d] mot[%d] = %d\n\n", b, z, o);
			o = 0;
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0' || original[i] == ';' || original[i] == '|')
				break ;
			if (box == 1)
				z++;
			box = 1;
		}
		z = 0;
		if (original[i] == '\0')
			break ;
		if (original[i] == '|')
		{
			parser[b].output.to_next_cmd = 1;
			i++;
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			parser[b + 1].input.pipe = 1;
		}
		if (original[i] == ';')
			i++;
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		b++;
	}
	printf("End\n");
}