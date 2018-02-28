/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 15:31:27 by vbaudot           #+#    #+#             */
/*   Updated: 2018/02/28 15:26:33 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		*ft_getenv(t_list **head, char *elem)
{
	t_list	*curr;
	int		len;

	curr = *head;
	len = ft_strlen(elem);
	while (curr)
	{
		if (ft_strncmp(curr->content, elem, len) == 0)
			return (&(curr->content)[len + 1]);
		curr = curr->next;
	}
	return ("");
}

static int	check_two_points(char *tmp, int i, int *j)
{
	*j = ++i;
	while (tmp[i])
	{
		if (tmp[i] == ':')
			break ;
		i++;
	}
	return (i);
}

char		*access_bin(int t[2], char *cmd, char *tmp, char *path)
{
	char	*final_path;

	while (42)
	{
		t[0] = check_two_points(tmp, t[0], &t[1]);
		path = ft_strsub(tmp, t[1], (t[0] - t[1]));
		final_path = ft_str3join(path, "/", cmd);
		free(path);
		if (access(final_path, F_OK) == 0)
		{
			if (access(final_path, X_OK) != 0)
			{
				ft_printf("minishell: not the rights: %s\n", cmd);
				free(tmp);
				free(final_path);
				exit(EXIT_FAILURE);
			}
			free(tmp);
			return (final_path);
		}
		free(final_path);
		if (!tmp[t[0]])
			break ;
	}
	return (NULL);
}

char		*ft_path(t_list **head, char *cmd)
{
	char	*tmp;
	char	*path;
	char	*rep;
	int		t[2];

	t[0] = -1;
	t[1] = 0;
	path = NULL;
	if (*head == NULL)
		tmp = ft_strdup("/bin:/usr/bin");
	else
		tmp = ft_strdup(ft_getenv(head, "PATH"));
	rep = ft_strdup(access_bin(t, cmd, tmp, path));
	if (rep != NULL)
		return (rep);
	ft_printf("minishell: command not found: %s\n", cmd);
	free(tmp);
	free(rep);
	exit(0);
}
