#include "ft_sh.h"

int				is_correct(char *original) //return -1 si a completer, 0 si fails
{
	int i;
	int o;
	int z;
	int b;
	int boite;
	char stock;
	int nbr_argv;

	b = 0;
	z = 0;
	o = 0;
	i = 0;
//	printf("\noriginal = %s\n\n", original);
	while (original[i])
	{
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		if (ft_isatoken(original[i]))
		{
//			printf("Unexpected token %c\n", original[i]);
			return (0);
		}
		nbr_argv = count_argv(i, original);
//		printf("\nnbr_argv = %d\n", nbr_argv);
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
	//				printf("Error de syntax\n");
					return (0);
				}
				if (boite == -1)
				{
	//				printf("je gere pas now\n");
					return (-4);
				}
				while ((original[i] == ' ' || original[i] == '\t') && original[i])
					i++;
				stock = checkquote(&i, &o, original);
				if (stock == 'k')
					break;
				else if (stock > '\0' && stock != 'n')
				{
	//				printf("Manque une quote %c \n", stock);
					if (stock == '"')
						return (-1);
					else
						return (-2);
				}
				i++;
				o++;
			}
	//		printf("commande [%d] mot[%d] = %d\n", b, z, o);
			o = 0;
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0' || original[i] == ';' || original[i] == '|')
				break ;
			z++;
		}
		z = 0;
		if (original[i] == '\0')
			break ;
		if (original[i] == '|')
		{
	//		printf("Ya un pipe\n"); //Faut un truc apres
			i++;
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0')
			{
	//			printf("faut une commande !\n");
				return (-3);
			}
		}
		if (original[i] == ';')
			i++;
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		if (original[i] && ft_isatoken(original[i]))
		{
	//		printf("Unexpected token %c\n", original[i]);
			return (0);
		}
		//Pas gere || et &&
		b++;
	}
	return (1);
}