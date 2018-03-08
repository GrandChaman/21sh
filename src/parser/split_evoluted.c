#include "ft_sh.h"

int		ft_isatoken(char c)
{
	if (c == ';' || c == '<' || c == '>' || c == '|')
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

	int nbr_redirection_input;
	int i_input;
	int nbr_redirection_output;
	int i_output;

	i_input = 0;
	i_output = 0;
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
		nbr_argv = count_argv(i, original);
		printf("---------------Ici nb argument = %d\n", nbr_argv);
		nbr_redirection_input = count_redirection_input(i, original);
		printf("++++++++++ nbr_redirection_input = %d\n", nbr_redirection_input);
		nbr_redirection_output = count_redirection_output(i, original);
		printf("************ nbr_redirection_output = %d\n", nbr_redirection_output);
		while (original[i] && original[i] != ';' && original[i] != '|')
		{
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0')
				break ;
			while ((original[i] != ' ' && original[i] != '\t' &&
			original[i] != ';' && original[i] != '|') && original[i])
			{
				if ((checkquote(&i, &o, original)) == 'k')
					break ;
				if (original[i] == '\0')
					break ;
				boite = redirections2(&i, original, parser, b, nbr_redirection_output - i_output);
				if (boite != 1)
				{
					if (boite == 2)
					{
						if (i_output == 0)
						{
							printf("malloc nbr de ouput = %d\n", nbr_redirection_output);
							parser[b].output.meta = malloc(sizeof(t_meta_output) * nbr_redirection_output);
							init_meta_output(parser, b, nbr_redirection_output);
						}
					}
					if (boite == 3)
					{
						if (i_input == 0)
						{
							printf("malloc nbr de input = %d\n", nbr_redirection_input);
							parser[b].input.meta = malloc(sizeof(t_meta_input) * nbr_redirection_input);
							init_meta_input(parser, b, nbr_redirection_input);
						}
					}
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
				printf("malloc parser[%d].output.name_file[%d] = %d\n", b, i_output, o);
				if (!(parser[b].output.meta[i_output].name = malloc(sizeof(char) * o + 1)))
					exit(0);
				i_output++;
			}
			if (box == 3)
			{
				while ((original[i] != ' ' && original[i] != '\t' &&
				original[i] != ';' && original[i] != '|') && original[i])
				{
					i++;
					o++;
				}
				printf("malloc parser[%d].input.name_file[%d] = %d\n", b , i_input ,o);
				if (!(parser[b].input.meta[i_input].name = malloc(sizeof(char) * o + 1)))
					exit(0);
				i_input++;
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
		i_input = 0;
		i_output = 0;
		if (original[i] == '\0')
			break ;
		if (original[i] == '|')
		{
			parser[b].output.pipe = 1;
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