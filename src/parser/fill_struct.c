#include "ft_sh.h"

static void there_is_space(t_vari *var, char *original)
{
	while ((original[var->i] == ' ' || original[var->i] == '\t') && original[var->i])
		var->i++;
}

static void	fill_backslashzero(t_vari *var, t_parser *parser)
{
	if (var->z >= 0 && var->o != 0 && var->box == 1)
	{
//		printf("rajoute cmd backslash\n");
		parser[var->b].cmd[var->j][var->o] = '\0';
		var->j++;
	}
	if (var->box == 2 && var->o != 0)
	{
		parser[var->b].output.meta[var->i_output].name[var->o] = '\0';
		var->i_output++;
		var->box = 1;
	}
	if (var->box == 3 && var->o != 0)
	{
		parser[var->b].input.meta[var->i_input].name[var->o] = '\0';
		var->i_input++;
		var->box = 1;
	}
}

static void fill_it(t_vari *var, t_parser *parser, char *original)
{
	if (var->boite == 1 && var->box == 1)
	{
	//	printf("fill_cmd parser[%d].cmd[%d][%d] = %c\n", var->b, var->j,var->o,  original[var->i]);
		parser[var->b].cmd[var->j][var->o] = original[var->i];
	}
	if (var->box == 3)
	{
	//	printf("fill_input = %c\n", original[var->i]);
		parser[var->b].input.meta[var->i_input].name[var->o] = original[var->i];
	}
	if (var->box == 2)
	{
	//	printf("fill_output = %c\n", original[var->i]);
		parser[var->b].output.meta[var->i_output].name[var->o] = original[var->i];
	}
}

static int	after_redirection(t_vari *var, t_parser *parser, char *original)
{
	if (var->boite == 4)
	{
		var->i_input++;					
		if (original[var->i] == '\0' || original[var->i] == ' ' || original[var->i] == '\t')
			return (0);
	}
	if (var->boite == 2)
	{
		var->box = var->boite;
		var->stock = checkquote_fill_output(var, original, parser);
		if (var->stock == 'n' || var->stock == 'k')
			return (0);
	}
	if (var->boite == 3)
	{
		var->box = var->boite;
		var->stock = checkquote_fill_input(var, original, parser);
		if (var->stock == 'n' || var->stock == 'k')
			return (0);
	}
	return (1);
}

static void	there_is_word(t_vari *var, t_parser *parser, char *original)
{
	while ((original[var->i] != ' ' && original[var->i] != '\t' &&
	original[var->i] != ';' && original[var->i] != '|') && original[var->i])
	{
		while (checkquote_fill_cmd(var, original, parser) != 'n')
			there_is_space(var, original);
		there_is_space(var, original);
		if (original[var->i] == '\0'|| original[var->i] == ';' || original[var->i] == '|')
			break ;
		var->boite = redirections4(original, parser, var);
		if (!(after_redirection(var, parser, original)))
			break ;
		fill_it(var, parser, original);
		var->i++;
		var->o++;
	}
}

static void reset_var(t_vari *var)
{
	var->box = 1;
	var->i_input = 0;
	var->i_output = 0;
	var->j = 0;
	var->z = 0;
}

static void end_fill_parser(t_vari *var, char *original)
{		
	if (original[var->i] == '|')
	{
		var->i++;
		there_is_space(var, original);
	}
	else
		var->i++;
	there_is_space(var, original);
	var->b++;
}

void		fill_parser(t_parser *parser, char *original)
{
	t_vari var;

	init_var(&var);
//	printf("\noriginal = %s\n", original);
	while (original[var.i])
	{
		there_is_space(&var, original);
		while (original[var.i] && original[var.i] != ';' && original[var.i] != '|')
		{
			there_is_space(&var, original);
			if (original[var.i] == '\0')
				break;
			there_is_word(&var, parser, original);
			fill_backslashzero(&var, parser);
			if (original[var.i] == '\0')
				break ;
			var.o = 0;
			var.z++;
		}
		if ((var.z > 0 || (var.z == 0 && original[var.i] == '\0')) && var.j)
			parser[var.b].cmd[var.j] = NULL;
		reset_var(&var);
		if (original[var.i] == '\0')
			break ;
		end_fill_parser(&var, original);
	}
//	ft_printf("End\n");
}
