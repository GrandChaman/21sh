/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:26:13 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/18 17:06:53 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static char		*extract_autocomplete_search(t_ft_sh *sh)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (!sh->buf.buf[0])
		return (NULL);
	while (sh->cursor - i > 0 && ft_iswhitespace(sh->buf.buf[sh->cursor - i]))
		i++;
	while (sh->cursor - i - len > 0 &&
		!ft_iswhitespace(sh->buf.buf[sh->cursor - i - len]))
		len++;
	return (ft_strndup(sh->buf.buf + (sh->cursor - i - len), len));
}

void		collect_data(char *str_part)
{
	t_ft_sh *sh;
	unsigned int save_cur;

	sh = get_ft_shell();
	save_cur = sh->cursor;
	collect_data_local_file(&sh->autocomplete, str_part);
	ft_lstsort(&sh->autocomplete, cmp_autoc_entry);
}


void		ft_sh_autocomplete(unsigned long touch)
{
	char *str_part;
	t_ft_sh *sh;
	unsigned int save_cur;

	sh = get_ft_shell();
	save_cur = sh->cursor;
	if (!sh->autocomplete && touch == T_TAB)
	{
		str_part = extract_autocomplete_search(sh);
		collect_data(str_part);
		prepare_autocomplete(sh, sh->autocomplete, save_cur);
		display_autocomplete(sh, sh->autocomplete);
		free(str_part);
	}
	else if (sh->autocomplete &&
		(touch == T_TAB || touch == T_LARR || touch == T_RARR ||
			touch == T_BARR || touch == T_TARR))
		move_in_autocompletion(touch);
}
