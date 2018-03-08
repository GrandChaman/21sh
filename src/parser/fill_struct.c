#include "ft_sh.h"

void		fill_parser(t_parser *parser, char *original)
{
	int i;
	int o;
	int z;
	int b;
	int boite;
	int box;
	int j;
	char stock;
	int i_output;
	int i_input;

	i_output = 0;
	i_input = 0;
	j = 0;
	b = 0;
	z = 0;
	o = 0;
	i = 0;
	box = 1;
	printf("\noriginal = %s\n", original);
	while (original[i])
	{
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		while (original[i] && original[i] != ';' && original[i] != '|')
		{
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0')
				break;
			while ((original[i] != ' ' && original[i] != '\t' &&
			original[i] != ';' && original[i] != '|') && original[i])
			{
				checkquote_fill_cmd(&i, original, parser, &b, &j);
				while ((original[i] == ' ' || original[i] == '\t') && original[i])
					i++;
				if (original[i] == '\0'|| original[i] == ';' || original[i] == '|')
					break ;
				boite = redirections4(&i, original);
				if (boite == 2)
				{
					box = boite;
					stock = checkquote_fill_output(&i, original, parser, &b, &i_output);
					if (stock == 'n' || stock == 'k')
						break ;
				}
				if (boite == 3)
				{
					box = boite;
					stock = checkquote_fill_input(&i, original, parser, &b, &i_input);
					if (stock == 'n' || stock == 'k')
						break ;
				}
				if (boite == 1 && box == 1)
				{
					printf("fill_cmd = %c\n", original[i]);
					parser[b].cmd[j][o] = original[i];
				}
				if (box == 3)
				{
					printf("fill_input = %c\n", original[i]);
					parser[b].input.meta[i_input].name[o] = original[i];
				}
				if (box == 2)
				{
					printf("fill_output = %c\n", original[i]);
					parser[b].output.meta[i_output].name[o] = original[i];
				}
				i++;
				o++;
			}
			if (z >= 0 && o != 0 && box == 1)
			{
				printf("rajoute cmd backslash\n");
				parser[b].cmd[j][o] = '\0';
				j++;
			}
			if (box == 2 && o != 0)
			{
				parser[b].output.meta[i_output].name[o] = '\0';
				i_output++;
				box = 1;
			}
			if (box == 3 && o != 0)
			{
				parser[b].input.meta[i_input].name[o] = '\0';
				i_input++;
				box = 1;
			}
			if (original[i] == '\0' || original[i] == ';' || original[i] == '|')
				break ;
			o = 0;
			z++;
		}

		box = 1;
		if ((z > 0 || (z == 0 && original[i] == '\0')) && j)
			parser[b].cmd[j] = NULL;
		/*if (i_input > 0) // a rajouter des trucs
			parser[b].input.meta[i_input] = NULL;
		if (i_output > 0)// a rajouter des trucs
			parser[b].output.meta[i_output] = NULL;*/
		i_input = 0;
		i_output = 0;
		j = 0;
		z = 0;
		if (original[i] == '\0')
			break ;
		if (original[i] == '|')
		{
			i++;
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
		}
		else
			i++;
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		b++;
	}
//	printf("End\n");
}