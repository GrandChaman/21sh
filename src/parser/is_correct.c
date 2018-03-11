#include "parser.h"

static int				this_is_word(t_vari *var, char *original)
{
<<<<<<< HEAD
	int		i;
	int		o;
	int		z;
	int		b;
	int		boite;
	char	stock;
	int		nbr_argv;

	b = 0;
	z = 0;
	o = 0;
	i = 0;
//	ft_printf("\noriginal = %s\n\n", original);
	while (original[i])
	{
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		if (ft_isatoken(original[i]))
		{
//			ft_printf("Unexpected token %c\n", original[i]);
			return (0);
		}
		nbr_argv = count_argv(i, original);
//		ft_printf("\nnbr_argv = %d\n", nbr_argv);
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
	//				ft_printf("Error de syntax\n");
					return (0);
				}
				if (boite == -1)
				{
	//				ft_printf("je gere pas now\n");
					return (-4);
				}
				while ((original[i] == ' ' || original[i] == '\t') && original[i])
					i++;
				stock = checkquote(&i, &o, original);
				if (stock == 'k')
					break;
				else if (stock > '\0' && stock != 'n')
				{
	//				ft_printf("Manque une quote %c \n", stock);
					if (stock == '"')
						return (-1);
					else
						return (-2);
				}
				i++;
				o++;
			}
	//		ft_printf("commande [%d] mot[%d] = %d\n", b, z, o);
			o = 0;
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0' || original[i] == ';' || original[i] == '|')
				break ;
			z++;
		}
		z = 0;
		if (original[i] == '\0')
=======
	while ((original[var->i] != ' ' && original[var->i] != '\t' &&
	original[var->i] != ';' && original[var->i] != '|') && original[var->i])
	{
		var->boite = redirections3(&var->i, original);
		if (var->boite == 0)
			return (0);
		if (var->boite == -1)
			return (-4);
		while ((original[var->i] == ' ' || original[var->i] == '\t') &&
			original[var->i])
			var->i++;
		if ((var->stock = checkquote(&var->i, &var->o, original)) == 'k')
>>>>>>> Parser
			break ;
		else if (var->stock > '\0' && var->stock != 'n')
		{
<<<<<<< HEAD
	//		ft_printf("Ya un pipe\n"); //Faut un truc apres
			i++;
			while ((original[i] == ' ' || original[i] == '\t') && original[i])
				i++;
			if (original[i] == '\0')
			{
	//			ft_printf("faut une commande !\n");
				return (-3);
			}
		}
		if (original[i] == ';')
			i++;
		while ((original[i] == ' ' || original[i] == '\t') && original[i])
			i++;
		if (original[i] && ft_isatoken(original[i]))
		{
	//		ft_printf("Unexpected token %c\n", original[i]);
=======
			if (var->stock == '"')
				return (-1);
			else
				return (-2);
		}
		var->i++;
		var->o++;
	}
	return (1);
}

static int				main_loop(t_vari *var, char *original)
{
	while (original[var->i] && original[var->i] != ';' &&
		original[var->i] != '|')
	{
		while ((original[var->i] == ' ' || original[var->i] == '\t') &&
			original[var->i])
			var->i++;
		if (original[var->i] == '\0')
			break ;
		if ((var->boite = this_is_word(var, original)) != 1)
			return (var->boite);
		var->o = 0;
		while ((original[var->i] == ' ' || original[var->i] == '\t') &&
			original[var->i])
			var->i++;
		if (original[var->i] == '\0' || original[var->i] == ';' ||
			original[var->i] == '|')
			break ;
		var->z++;
	}
	return (1);
}

static int				there_is_pipe(t_vari *var, char *original)
{
	if (original[var->i] == '|')
	{
		var->i++;
		while ((original[var->i] == ' ' || original[var->i] == '\t') &&
			original[var->i])
			var->i++;
		if (original[var->i] == '\0')
			return (-3);
	}
	return (1);
}

static int				second_main_loop(t_vari *var, char *original)
{
	if ((var->boite = there_is_pipe(var, original)) != 1)
		return (var->boite);
	if (original[var->i] == ';')
		var->i++;
	while ((original[var->i] == ' ' || original[var->i] == '\t') &&
		original[var->i])
		var->i++;
	if (original[var->i] && ft_isatoken(original[var->i]))
		return (0);
	return (1);
}

int				is_correct(char *original)
{
	t_vari var;

	init_var(&var);
	while (original[var.i])
	{
		while ((original[var.i] == ' ' || original[var.i] == '\t') &&
			original[var.i])
			var.i++;
		if (ft_isatoken(original[var.i]))
>>>>>>> Parser
			return (0);
		var.nbr_argv = count_argv(var.i, original);
		if ((var.boite = main_loop(&var, original)) != 1)
			return (var.boite);
		var.z = 0;
		if (original[var.i] == '\0')
			break ;
		if ((var.boite = second_main_loop(&var, original)) == 1)
			return (var.boite);
		var.b++;
	}
	return (1);
}
