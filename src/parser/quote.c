#include "ft_sh.h"

char	checkquote(int *i, int *o, char *original) // effet '' ?
{
	char tableau[4] = "\"'`";
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

char	checkquote_fill_cmd(int *i, char *original, t_parser *parser, int *b, int *j)
{
	char tableau[4] = "\"'`";
	int var;
	int stock;

	var = 0;
	while (tableau[var])
	{
		if (original[*i] == tableau[var])
		{
			stock = checkquote2_fill_cmd(i, original, tableau[var], parser, b, j);
			if (stock == 0)
				return ('k'); //sert a rien, peux return un int
		}
		var++;
	}
	return ('n');
}

int		checkquote2_fill_cmd(int *i, char *original, char c, t_parser *parser, int *b, int *j)
{
	int o;

	o = 0;
	if (original[*i] && original[*i] == c)
	{
		*i = *i + 1;
		while (original[*i] && original[*i] != c)
		{
			parser[*b].cmd[*j][o] = original[*i];
			*i = *i + 1;
			o = o + 1;
		}
		parser[*b].cmd[*j][o] = '\0';
		*j = *j + 1;
		*i = *i + 1;
		return (0) ;
	}
	return (1);
}

char	checkquote_fill_output(int *i, char *original, t_parser *parser, int *b)
{
	char tableau[4] = "\"'`";
	int var;
	int stock;

	var = 0;
	while (tableau[var])
	{
		if (original[*i] == tableau[var])
		{
			stock = checkquote2_fill_output(i, original, tableau[var], parser, b);
			if (stock == 0)
				return ('k'); //sert a rien, peux return un int
		}
		var++;
	}
	return ('n');
}

int		checkquote2_fill_output(int *i, char *original, char c, t_parser *parser, int *b)
{
	int o;

	o = 0;
	if (original[*i] && original[*i] == c)
	{
		*i = *i + 1;
		while (original[*i] && original[*i] != c)
		{
			parser[*b].output.name_file[o] = original[*i];
			*i = *i + 1;
			o = o + 1;
		}
		parser[*b].output.name_file[o] = '\0';
		*i = *i + 1;
		return (0) ;
	}
	return (1);
}

char	checkquote_fill_input(int *i, char *original, t_parser *parser, int *b)
{
	char tableau[4] = "\"'`";
	int var;
	int stock;

	var = 0;
	while (tableau[var])
	{
		if (original[*i] == tableau[var])
		{
			stock = checkquote2_fill_intput(i, original, tableau[var], parser, b);
			if (stock == 0)
				return ('k'); //sert a rien, peux return un int
		}
		var++;
	}
	return ('n');
}

int		checkquote2_fill_intput(int *i, char *original, char c, t_parser *parser, int *b)
{
	int o;

	o = 0;
	if (original[*i] && original[*i] == c)
	{
		*i = *i + 1;
		while (original[*i] && original[*i] != c)
		{
			parser[*b].input.name_file[o] = original[*i];
			*i = *i + 1;
			o = o + 1;
		}
		parser[*b].input.name_file[o] = '\0';
		*i = *i + 1;
		return (0) ;
	}
	return (1);
}
