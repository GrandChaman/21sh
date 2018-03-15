/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_autocomplete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:26:13 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/15 16:32:23 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		display_autocomplete(unsigned long touch)
{
	int i;
	char *str_part;
	t_ft_sh *sh;

	sh = get_ft_shell();
	i = 0;
	(void)touch;
	while (sh->cursor - i > 0 && ft_iswhitespace(sh->buf.buf[sh->cursor - i]))
		i++;
	str_part = (!i ? NULL : ft_strndup(sh->buf.buf + sh->cursor - i, i));
	collect_data(str_part);
	free(str_part);
}
