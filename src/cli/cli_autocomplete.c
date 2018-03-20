/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:26:13 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/20 18:23:11 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static char				*extract_autocomplete_search(t_ft_sh *sh)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (!sh->cursor || ft_iswhitespace(sh->buf.buf[sh->cursor - 1]))
		return (NULL);
	while (sh->cursor - i > 0 && ft_iswhitespace(sh->buf.buf[sh->cursor - i]))
		i++;
	while (sh->cursor - i - len > 0 &&
		!ft_iswhitespace(sh->buf.buf[sh->cursor - i - len]))
		len++;
	return (ft_strndup(sh->buf.buf + (sh->cursor - i - len) +
		(sh->cursor - i - len > 0), len - (sh->cursor - i - len > 0)));
}

void					collect_data(char *str_part)
{
	t_ft_sh			*sh;
	unsigned int	save_cur;

	sh = get_ft_shell();
	save_cur = sh->cursor;
	collect_data_local_file(&sh->autocomplete, str_part);
	ft_lstsort(&sh->autocomplete, cmp_autoc_entry);
}

static void				complete_missing_autocomplete(t_ft_sh *sh,
	char *str_part)
{
	t_ft_autoc_entry	*entry;
	int					i;
	char				*tmp;

	i = 0;
	if (!sh->autocomplete_cusor)
		return ;
	entry = (t_ft_autoc_entry*)sh->autocomplete_cusor->content;
	if (!str_part || !(tmp = ft_strrchr(str_part, '/')))
		tmp = str_part;
	if (tmp && tmp[0] == '/')
		tmp++;
	while (entry->name[i])
		if (tmp && entry->name[i] == tmp[i])
			i++;
		else
			break ;
	insert_in_cli(entry->name + i);
}

void					ft_sh_autocomplete(unsigned long touch)
{
	char			*str_part;
	t_ft_sh			*sh;
	unsigned int	save_cur;

	sh = get_ft_shell();
	str_part = NULL;
	str_part = extract_autocomplete_search(sh);
	if (!sh->autocomplete && touch == T_TAB)
	{
		collect_data(str_part);
		save_cur = sh->cursor;
		prepare_autocomplete(sh, sh->autocomplete, save_cur);
		display_autocomplete(sh, sh->autocomplete);
	}
	else if (sh->autocomplete &&
		(touch == T_TAB || touch == T_LARR || touch == T_RARR))
		move_in_autocompletion(touch);
	if (touch == T_ENTER || (sh->autocomplete && !sh->autocomplete->next &&
		!sh->autocomplete->prev && (sh->autocomplete_cusor = sh->autocomplete)))
	{
		complete_missing_autocomplete(sh, str_part);
		cancel_autocompletion(sh, 0);
	}
	free(str_part);
}
