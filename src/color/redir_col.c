/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:33:45 by awyart            #+#    #+#             */
/*   Updated: 2018/03/12 14:32:32 by awyart           ###   ########.fr       */
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
	printspace(list);
	while (is_dlist_word(*list) && !is_token(*list))
	{
		printcyn(*list);
		*list = (*list)->next;
	}
	printspace(list);
}