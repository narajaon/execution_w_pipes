/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:40:51 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				handle_del(t_dlist_wrap *wrap)
{
	t_dlist *todel;

	todel = NULL;
	if ((todel = cur_list(wrap)) == NULL)
		return (0);
	if (todel == wrap->head && todel->next == NULL)
		wrap->head = NULL;
	if (todel->prev)
		todel->prev->next = todel->next;
	if (todel->next)
	{
		if (todel == wrap->head)
			wrap->head = todel->next;
		todel->next->prev = todel->prev;
	}
	todel->prev = NULL;
	todel->next = NULL;
	ft_dlist_free(&todel, ft_memdel);
	wrap->pos--;
	wrap->size--;
	return (1);
}

int				handle_del_right(t_dlist_wrap *wrap)
{
	t_dlist *todel;

	todel = NULL;
	if ((todel = cur_list(wrap)) == NULL)
		return (0);
	if (todel->next == NULL)
	{
		if (wrap->head == todel)
			wrap->head = NULL;
		else
			return (0);
	}
	else
		todel = todel->next;
	if (todel->prev)
		todel->prev->next = todel->next;
	if (todel->next)
		todel->next->prev = todel->prev;
	todel->prev = NULL;
	todel->next = NULL;
	ft_dlist_free(&todel, ft_memdel);
	wrap->size--;
	return (1);
}
