/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 10:34:34 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/22 10:46:29 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		gen_hash(t_list *env, t_wait_el *el)
{
	t_ft_sh *sh;

	el->pid = 0;
	sh = get_ft_shell();
	if (sh->ht)
	{
		free_hash_table(&sh->ht);
		sh->ht = NULL;
		ft_printf("Hash table free'd\n");
	}
	if (!env || !ft_lstfind(env, "PATH", compare_with_key))
	{
		el->pid = 1;
		return (ft_printf("hash: Can't generate the hash table because"
			" PATH is not defined\n") && 1);
	}
	sh->ht = load_bin_into_hash_table(env);
	if (sh->ht)
		ft_printf("Hash table generated\n");
	return (0);
}
