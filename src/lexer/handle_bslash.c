/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 15:55:24 by awyart            #+#    #+#             */
/*   Updated: 2017/12/14 21:32:58 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_handle_backslash(t_dlist **line)
{
	t_dlist	*list;
	t_chr	*schar;
	t_dlist *tmp;

	list = *line;
	schar = NULL;
	tmp = NULL;
	while (list != NULL)
	{
		schar = list->content;
		if (schar->c == '\\' && schar->is_escaped != '1')
		{
			if (list->next)
			{
				schar = list->next->content;
				schar->is_escaped = '1';
			}
			tmp = list;
		}
		list = list->next;
		if (tmp != NULL)
			ft_dlist_delone(&tmp);
	}
}
