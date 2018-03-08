/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/08 13:55:27 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_mv_tmp(t_dlist_wrap *wrap)
{
	t_dlist	*list;
	int		count;

	count = 0;
	list = wrap->tmp;
	while (list != NULL)
	{
		list = list->prev;
		count++;
	}
	return (count);
}

int	move_right(t_dlist_wrap *wrap)
{
	if (wrap->pos >= wrap->size)
		return (0);
	wrap->pos++;
	return (1);
}

int	move_left(t_dlist_wrap *wrap)
{
	if (wrap->pos <= 0)
		return (0);
	if (wrap->tmp != NULL && wrap->pos <= check_mv_tmp(wrap))
		return (0);
	wrap->pos--;
	return (1);
}
