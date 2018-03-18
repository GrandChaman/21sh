#include "ft_sh.h"

void		is_space(int *i, char *original)
{
	while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
		*i = *i + 1;
}

static void	redirection_count(char *original, int *i, int *o, int *nb)
{
	if (redirections_output(i, original) != 1)
	{
		*nb = *nb + 1;
		checkquote(i, o, original);
	}
}

static int	count_redirection_output_2(char *original, int i, int o, int nb)
{
	while (original[i])
	{
		is_space(&i, original);
		while ((original[i] != ' ' && original[i] != '\t') && original[i])
		{
			checkquote(&i, &o, original);
			is_space(&i, original);
			if (original[i] == '|' || original[i] == ';')
				return (nb);
			if (original[i] == '\0')
				break ;
			redirection_count(original, &i, &o, &nb);
			if (original[i] == '|' || original[i] == ';')
				return (nb);
			i++;
		}
		is_space(&i, original);
		if (original[i] == '\0')
			break ;
		if (original[i] == '|' || original[i] == ';')
			return (nb);
	}
	return (nb);
}

int			count_redirection_output(int i, char *original)
{
	int nb;
	int o;

	o = 0;
	nb = 0;
	return (count_redirection_output_2(original, i, o, nb));
}