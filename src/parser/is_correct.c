#include "ft_sh.h"

int				is_correct(char *original) //return -1 si a completer, 0 si fails
{
	t_vari var;
	init_var(&var);

	printf("\noriginal = %s\n\n", original);
	while (original[var.i])
	{
		while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
			var.i++;
		if (ft_isatoken(original[var.i]))
		{
			printf("Unexpected token %c\n", original[var.i]);
			return (0);
		}
		var.nbr_argv = count_argv(var.i, original);
		while (original[var.i] && original[var.i] != ';' && original[var.i] != '|')
		{
			while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
				var.i++;
			if (original[var.i] == '\0')
				break;
			while ((original[var.i] != ' ' && original[var.i] != '\t' &&
			original[var.i] != ';' && original[var.i] != '|') && original[var.i])
			{
				var.boite = redirections3(&var.i, original);
				if (var.boite == 0)
				{
					printf("Error de syntax\n");
					return (0);
				}
				if (var.boite == -1)
				{
					printf("je gere pas now\n");
					return (-4);
				}
				while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
					var.i++;
				var.stock = checkquote(&var.i, &var.o, original);
				if (var.stock == 'k')
					break;
				else if (var.stock > '\0' && var.stock != 'n')
				{
					printf("Manque une quote %c \n", var.stock);
					if (var.stock == '"')
						return (-1);
					else
						return (-2);
				}
				var.i++;
				var.o++;
			}
			var.o = 0;
			while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
				var.i++;
			if (original[var.i] == '\0' || original[var.i] == ';' || original[var.i] == '|')
				break ;
			var.z++;
		}
		var.z = 0;
		if (original[var.i] == '\0')
			break ;
		if (original[var.i] == '|')
		{
			printf("Ya un pipe\n");
			var.i++;
			while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
				var.i++;
			if (original[var.i] == '\0')
			{
				printf("faut une commande !\n");
				return (-3);
			}
		}
		if (original[var.i] == ';')
			var.i++;
		while ((original[var.i] == ' ' || original[var.i] == '\t') && original[var.i])
			var.i++;
		if (original[var.i] && ft_isatoken(original[var.i]))
		{
			printf("Unexpected token %c\n", original[var.i]);
			return (0);
		}
		var.b++;
	}
	return (1);
}