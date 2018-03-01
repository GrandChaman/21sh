#include "ft_sh.h"

int		redirections(int *i, int *increment_something, char *original)
{
	if (original[*i] && original[*i] == '<') //a gere les erreurs
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '<')
		{
			*i = *i + 1;
	//		printf("Cas ultra special a gere apres\n");
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			// juste recupere un char * et le passer a victor ^^ avec pipe avoir quoi ecrire
		}
		else
		{
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			*increment_something = *increment_something + 1;
		}
	}
	if (original[*i] && original[*i] == '>')
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '>')
		{
			*i = *i + 1;
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			*increment_something = *increment_something + 1;
		}
		else
		{
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			*increment_something = *increment_something + 1;
		}
	}
	return (1);
}

int		redirections2(int *i, char *original, t_parser *parser, int b)
{
	if (original[*i] && original[*i] == '<') //a gere les erreurs
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '<')
		{
			*i = *i + 1;
//			printf("Cas ultra special a gere apres\n");
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			// juste recupere un char * et le passer a victor ^^ avec pipe avoir quoi ecrire
		}
		else
		{
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			parser[b].entree_cmd.exist = 1;
			return (3);
		}
	}
	if (original[*i] && original[*i] == '>')
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '>')
		{
			*i = *i + 1;
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			parser[b].sortie_cmd.double_chevron = 1;
			return (2);
		}
		else
		{
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (2);
		}
	}
	return (1);
}

int		redirections3(int *i, char *original)
{
	if (original[*i] && original[*i] == '<') //a gere les erreurs
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '<')
		{
			*i = *i + 1;
//			printf("Cas ultra special a gere apres\n");
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (-1);
			// juste recupere un char * et le passer a victor ^^ avec pipe avoir quoi ecrire
		}
		else
		{
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (3);
		}
	}
	if (original[*i] && original[*i] == '>')
	{
		*i = *i + 1;
		if (original[*i] && original[*i] == '>')
		{
			*i = *i + 1;
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (2);
		}
		else
		{
			while ((original[*i] == ' ' || original[*i] == '\t') && original[*i])
				*i = *i + 1;
			if (original[*i] == '\0' || ft_isatoken(original[*i]))
				return (0);
			return (2);
		}
	}
	return (1);
}
