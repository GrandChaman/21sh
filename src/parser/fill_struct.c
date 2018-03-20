#include "ft_sh.h"

static void	fill_backslashzero(t_vari *var, t_parser *parser)
{
	if (var->z >= 0 && var->o != 0 && var->box == 1 && var->boite != 4)
	{
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

static void fill_it(t_vari *var, t_parser *parser, char *ori)
{
	if (var->boite == 1 && var->box == 1)
	{
		parser[var->b].cmd[var->j][var->o] = ori[var->i];
	}
	if (var->box == 3)
	{
		parser[var->b].input.meta[var->i_input].name[var->o] = ori[var->i];
	}
	if (var->box == 2)
	{
		parser[var->b].output.meta[var->i_output].name[var->o] = ori[var->i];
	}
}

static int	after_redirection(t_vari *var, t_parser *parser, char *ori)
{
	if (var->boite == 4)
	{
		var->i_input++;
		if (ori[var->i] == '\0' || ori[var->i] == ' ' || ori[var->i] == '\n')
			return (0);
	}
	if (var->boite == 2)
	{
		var->box = var->boite;
		var->stock = checkquote_fill_output(var, ori, parser);
		if (var->stock == 'n' || var->stock == 'k')
			return (0);
	}
	if (var->boite == 3)
	{
		var->box = var->boite;
		var->stock = checkquote_fill_input(var, ori, parser);
		if (var->stock == 'n' || var->stock == 'k')
			return (0);
	}
	return (1);
}

static void	there_is_word(t_vari *var, t_parser *parser, char *ori)
{
	while ((ori[var->i] != ' ' && ori[var->i] != '\n' &&
	ori[var->i] != ';' && ori[var->i] != '|') && ori[var->i])
	{
		while (checkquote_fill_cmd(var, ori, parser) != 'n')
			there_is_space(var, ori);
		there_is_space(var, ori);
		if (ori[var->i] == '\0' || ori[var->i] == ';' || ori[var->i] == '|')
			break ;
		var->boite = redirections4(ori, parser, var);
		if (!(after_redirection(var, parser, ori)))
			break ;
		fill_it(var, parser, ori);
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

static void end_fill_parser(t_vari *var, char *ori)
{		
	if (ori[var->i] == '|')
	{
		var->i++;
		there_is_space(var, ori);
	}
	else
		var->i++;
	there_is_space(var, ori);
	var->b++;
}

void		fill_parser(t_parser *parser, char *ori)
{
	t_vari var;

	init_var(&var);
	while (ori[var.i])
	{
		there_is_space(&var, ori);
		while (ori[var.i] && ori[var.i] != ';' && ori[var.i] != '|')
		{
			there_is_space(&var, ori);
			if (ori[var.i] == '\0')
				break;
			there_is_word(&var, parser, ori);
			fill_backslashzero(&var, parser);
			if (ori[var.i] == '\0')
				break ;
			var.o = 0;
			var.z++;
		}
		if ((var.z > 0 || (var.z == 0 && ori[var.i] == '\0')) && var.j)
			parser[var.b].cmd[var.j] = NULL;
		reset_var(&var);
		if (ori[var.i] == '\0')
			break ;
		end_fill_parser(&var, ori);
	}
}
