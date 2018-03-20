/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:33:42 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/20 17:54:59 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_bin_hash		*get_elem_from_ht(t_bin_hash_table *ht, char *name)
{
	unsigned long index;
	unsigned long hash;
	index = dj2b_hash(name) % ht->size;
	hash = index;
	ft_fprintf(get_ft_shell()->debug_tty, "Yoplait : %d - %d\n", index, ht->size);
	while (index - hash < ht->size && (!ht->table[index % ht->size].name ||
		ft_strcmp(ht->table[index % ht->size].name, name)))
		{
			ft_fprintf(get_ft_shell()->debug_tty, "Try : %s - %s - %d\n",
				ht->table[index % ht->size].name, name, index);
			index++;
		}
	ft_fprintf(get_ft_shell()->debug_tty, "Ended : %d - %d\n", hash, index);
	if (index - hash >= ht->size)
		return (NULL);
	return (&(ht->table[index % ht->size]));
}
