/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:33:45 by awyart            #+#    #+#             */
/*   Updated: 2018/03/09 17:27:29 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void check_redir(t_dlist **list)
{
	if (is_token(*list))
	{
		while (*list != NULL && is_token(*list))
		{
			printgreen(*list);
			*list = (*list)->next;
		}
	}
	if (is_token(*list))
		return ;
	dprintf(g_fd, "check_args\n");
	check_args(list);
}