/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete_ht.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:29:28 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/21 16:51:20 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void			collect_data_ht(t_list **list, char *str_part)
{
	t_ft_autoc_entry	entry;
	unsigned int		i;
	t_ft_sh				*sh;
	size_t				len;


	sh = get_ft_shell();
	ft_fprintf(sh->debug_tty, "TOTO");
	if (!sh->ht || !str_part)
		return ;
	entry.undeline = 0;
	entry.color = ANSI_COLOR_CYAN;
	i = 0;
	len = ft_strlen(str_part);
	ft_fprintf(sh->debug_tty, "TOTO");

	while (i < sh->ht->size)
	{
		ft_fprintf(sh->debug_tty, "TOTO : %s %d\n", sh->ht->table[i].name, !ft_stralike(str_part, sh->ht->table[i].name, len));
		if (!ft_stralike(str_part, sh->ht->table[i].name, len))
		{
			entry.name = ft_strdup(sh->ht->table[i].name);
			ft_lstpush_back(list, &entry, sizeof(t_ft_autoc_entry));
		}
		i++;
	}
}
