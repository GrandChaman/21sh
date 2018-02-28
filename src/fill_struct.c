#include "ft_sh.h"

int		fill_parser(t_parser *parser, char *original)
{
	int i;
	int o;
	int z;
	int b;
	int boite;
	char stock;
	int j;

	j = 0;
	b = 0;
	z = 0;
	o = 0;
	i = 0;
	//printf("\noriginal = %s\n\n", original);
	while (original[i])
	{
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		if (ft_isatoken(original[i]))
		{
			printf("Unexpected token %c\n", original[i]);
			return (0);
		}
		while (original[i] && original[i] != ';' && original[i] != '|')
		{
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0')
				break;
			while ((original[i] != ' ' && original[i] != '\t' &&
			original[i] != ';' && original[i] != '|') && original[i])
			{
				boite = redirections3(&i, original);
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
					return (-1);
				}
				if (z == 0)
					parser[b].name_cmd[o] = original[i];
				i++;
				o++;
			}
	//		printf("commande [%d] mot[%d] = %d\n", b, z, o);
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
			i++;
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0')
			{
				printf("faut une commande !\n");
				return (-1);
			}
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
	printf("name_cmd = %s\n", parser[0].name_cmd);
	return (1);
}