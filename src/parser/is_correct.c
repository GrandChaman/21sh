#include "ft_sh.h"

static int				this_is_word(t_vari *var, char *original)
{
	while ((original[var->i] != ' ' && original[var->i] != '\n' &&
	original[var->i] != ';' && original[var->i] != '|') && original[var->i])
	{
		var->boite = redirections3(&var->i, original);
		if (var->boite == 0)
			return (0);
		if (var->boite == -1)
			return (-4);
		while ((original[var->i] == ' ' || original[var->i] == '\n') &&
			original[var->i])
			var->i++;
		if ((var->stock = checkquote(&var->i, &var->o, original)) == 'k')
			break ;
		else if (var->stock > '\0' && var->stock != 'n')
		{
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
		while ((original[var->i] == ' ' || original[var->i] == '\n') &&
			original[var->i])
			var->i++;
		if (original[var->i] == '\0')
			break ;
		if ((var->boite = this_is_word(var, original)) != 1)
			return (var->boite);
		var->o = 0;
		while ((original[var->i] == ' ' || original[var->i] == '\n') &&
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
		while ((original[var->i] == ' ' || original[var->i] == '\n') &&
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
	while ((original[var->i] == ' ' || original[var->i] == '\n') &&
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
		while ((original[var.i] == ' ' || original[var.i] == '\n') &&
			original[var.i])
			var.i++;
		if (ft_isatoken(original[var.i]))
			return (0);
		var.nbr_argv = count_argv(var.i, original);
		if ((var.boite = main_loop(&var, original)) != 1)
			return (var.boite);
		var.z = 0;
		if (original[var.i] == '\0')
			break ;
		if ((var.boite = second_main_loop(&var, original)) != 1)
			return (var.boite);
		var.b++;
	}
	return (1);
}
