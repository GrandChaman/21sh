#include "ft_sh.h"

char	checkquote(int *i, int *o, char *original)
{
	char tableau[4] = "\"'";
	int var;
	int stock;

	var = 0;
	while (tableau[var])
	{
		if (original[*i] == tableau[var])
		{
			stock = checkquote2(i, o, original, tableau[var]);
			if (stock == 0)
				return ('k');
			if (stock == -1)
			{
				return (tableau[var]);
			}
		}
		var++;
	}
	return ('n');
}

int		checkquote2(int *i, int *o, char *original, char c)
{
	if (original[*i] && original[*i] == c)
	{
		*i = *i + 1;
		while (original[*i] && original[*i] != c)
		{
			*i = *i + 1;
			*o = *o + 1;
		}
		if (original[*i] == '\0' && original[*i] != c)
			return (-1);
		*i = *i + 1;
		return (0) ;
	}
	return (1);
}

char	checkquote_fill_cmd(t_vari *var, char *original, t_parser *parser)
{
	char tableau[4] = "\"'";
	int i;
	int stock;

	i = 0;
	while (tableau[i])
	{
		if (original[var->i] == tableau[i])
		{
			stock = checkquote2_fill_cmd(var, original, tableau[i], parser);
			if (stock == 0)
			{
				return ('k'); // sert a rien peux retourner un int
			}
		}
		i++;
	}
	return ('n');
}

int		checkquote2_fill_cmd(t_vari *var, char *original, char c, t_parser *parser)
{
	int o;

	o = 0;
	if (original[var->i] && original[var->i] == c)
	{
		var->i++;
		while (original[var->i] && original[var->i] != c)
		{
//			printf("quote fill = %c\n", original[var->i]);
			parser[var->b].cmd[var->j][o] = original[var->i];
			var->i++;
			o = o + 1;
		}
		parser[var->b].cmd[var->j][o] = '\0';
		var->j++;
		var->i++;
		return (0) ;
	}
	return (1);
}

char	checkquote_fill_output(t_vari *var, char *original, t_parser *parser)
{
	char tableau[4] = "\"'";
	int i;
	int stock;

	i = 0;
	while (tableau[i])
	{
		if (original[var->i] == tableau[i])
		{
			stock = checkquote2_fill_output(var, original, tableau[i], parser);
			if (stock == 0)
				return ('k'); //sert a rien, peux return un int
		}
		i++;
	}
	return ('n');
}

int		checkquote2_fill_output(t_vari *var, char *original, char c, t_parser *parser)
{
	int o;

	o = 0;
	if (original[var->i] && original[var->i] == c)
	{
		var->i++;
		while (original[var->i] && original[var->i] != c)
		{
			parser[var->b].output.meta[var->i_output].name[o] = original[var->i];
			var->i++;
			o = o + 1;
		}
		parser[var->b].output.meta[var->i_output].name[o] = '\0';
		var->i++;
		var->i_output++;
		return (0) ;
	}
	return (1);
}

char	checkquote_fill_input(t_vari *var, char *original, t_parser *parser)
{
	char tableau[4] = "\"'";
	int i;
	int stock;

	i = 0;
	while (tableau[i])
	{
		if (original[var->i] == tableau[i])
		{
			stock = checkquote2_fill_intput(var, original, tableau[i], parser);
			if (stock == 0)
				return ('k'); //sert a rien, peux return un int
		}
		i++;
	}
	return ('n');
}

int		checkquote2_fill_intput(t_vari *var, char *original, char c, t_parser *parser)
{
	int o;

	o = 0;
	if (original[var->i] && original[var->i] == c)
	{
		var->i++;
		while (original[var->i] && original[var->i] != c)
		{
			parser[var->b].input.meta[var->i_input].name[o] = original[var->i];
			var->i++;
			o = o + 1;
		}
		parser[var->b].input.meta[var->i_input].name[o] = '\0';
		var->i_input++;
		var->i++;
		return (0) ;
	}
	return (1);
}
