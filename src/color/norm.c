/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:22:07 by awyart            #+#    #+#             */
/*   Updated: 2018/03/09 17:20:03 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void printspace(t_dlist **list)
{
	while (is_dlist_space(*list))
	{
		printwhite(*list);
		*list = (*list)->next;
	}
}


void check_cmd(t_dlist **list)
{
	printspace(list);
	if (is_token(*list))
		return ;
	while (is_dlist_word(*list) && !is_token(*list))
	{
		printred(*list);
		*list = (*list)->next;
	}
	printspace(list);
}

void check_args(t_dlist **list)
{
	
	while (is_token(*list) == 0)
	{
		if (*list == NULL)
			break ;
		printspace(list);
		if (is_dlist_opt(*list))
		{
			while (is_dlist_word(*list) && !is_token(*list))
			{
				printyellow(*list);
				*list = (*list)->next;
			}
		}
		else
		{
			while (is_dlist_word(*list) && !is_token(*list))
			{
				printcyn(*list);
				*list = (*list)->next;
			}
		}
		printspace(list);
	}
}

void check_norm(t_dlist **list)
{
	if (is_token(*list))
	{
		dprintf(g_fd, "token\n");
		while (*list != NULL && is_token(*list))
		{
			printblue(*list);
			*list = (*list)->next;
		}
	}
	dprintf(g_fd, "check_cmd\n");
	check_cmd(list);
	if (is_token(*list))
		return ;
	dprintf(g_fd, "check_option\n");
	if (is_token(*list))
		return ;
	dprintf(g_fd, "check_args\n");
	check_args(list);
}