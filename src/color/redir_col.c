/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:33:45 by awyart            #+#    #+#             */
/*   Updated: 2018/03/20 15:08:13 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_redir(t_dlist **list)
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

void	printblue(t_dlist *list)
{
	t_chr	*schar;
	t_chr	*prev;
	t_chr	*prev2;

	schar = NULL;
	prev = NULL;
	prev2 = NULL;
	if (list != NULL)
	{
		if (list->prev != NULL)
		{
			prev = list->prev->content;
			if (list->prev->prev != NULL)
				prev2 = list->prev->prev->content;
		}
		schar = list->content;
		if (schar->c == '\\')
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KWHT, schar->c, KNRM);
		else if (prev && prev->c == '\\' && prev2->c != '\\')
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KWHT, schar->c, KNRM);
		else
			ft_dprintf(STDOUT_FILENO, "%s%c%s", KBLU, schar->c, KNRM);
	}
}
