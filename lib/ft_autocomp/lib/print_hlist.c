/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hlist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:43:13 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:43:43 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/levenshtein.h"

void		print_hlst_content(t_dlist *list)
{
	char	*c;
	t_chr	*content;

	content = list->content;
	printf("|%c|", content->c);
}

void		hl_print_next(t_dlist *list, void (*print)())
{
	while (list)
	{
		print(list);
		list = list->next;
	}
}
