#include "parser.h"

static void	main_loop(int *i, int o, int *nb, char *original)
{
	while ((checkquote(i, &o, original)) == 'k')
	{
		*nb = *nb + 1;
		while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
			*i = *i + 1;
	}
	while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
		*i = *i + 1;
}

static void	space(int *i, char *original)
{
	while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
		*i = *i + 1;
}

static int	main_loop2(int i, int o, int nb, char *original)
{
	while (original[i])
	{
		space(&i, original);
		while ((original[i] != ' ' && original[i] != '\t') && original[i])
		{
			main_loop(&i, o, &nb, original);
			if (original[i] == '|' || original[i] == ';')
				break ;
			if (original[i] == '\0' && (nb = nb - 1))
				break ;
			if ((redirections3(&i, original)) != 1 &&
				(checkquote(&i, &o, original)))
				nb = nb - 1;
			if (original[i] == '|' || original[i] == ';')
				return (nb);
			i++;
		}
		nb++;
		space(&i, original);
		if (original[i] == '\0')
			break ;
		if (original[i] == '|' || original[i] == ';')
			return (nb);
	}
	return (nb);
}

int			count_argv(int i, char *original)
{
	int nb;
	int o;

	o = 0;
	nb = 0;
	return (main_loop2(i, o, nb, original));
}