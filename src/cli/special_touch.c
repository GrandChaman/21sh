/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_touch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 15:28:41 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/06 10:22:40 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		spt_delete(unsigned long touch)
{
	t_ft_sh *shell;

	(void)touch;
	shell = get_ft_shell();
	if (shell->cursor <= 0)
		return ;
	dbuf_remove(&shell->buf, shell->cursor);
	exec_term_command(TC_DELETE);
}

void		spt_arrow(unsigned long touch)
{
	move_in_terminal(touch, 1);
}
