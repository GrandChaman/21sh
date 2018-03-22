/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:33:42 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/22 10:51:01 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_bin_hash		*get_elem_from_ht(t_bin_hash_table *ht, char *name)
{
	unsigned long index;
	unsigned long hash;

	if (!ht || !name || !ht->size)
		return (NULL);
	index = dj2b_hash(name) % ht->size;
	hash = index;
	while (index - hash < ht->size && (!ht->table[index % ht->size].name ||
		ft_strcmp(ht->table[index % ht->size].name, name)))
		index++;
	if (index - hash >= ht->size)
		return (NULL);
	return (&(ht->table[index % ht->size]));
}
