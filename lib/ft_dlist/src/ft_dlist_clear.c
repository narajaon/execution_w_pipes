/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 17:55:12 by awyart            #+#    #+#             */
/*   Updated: 2017/12/14 17:10:21 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void				ft_dlist_clear(t_dlist **list, void (*free_ptr)(void **))
{
	t_dlist			*tmp;
	t_dlist			*curr;

	curr = *list;
	while (curr != NULL)
	{
		tmp = curr;
		free_ptr((void **)(&(tmp->content)));
		ft_memdel((void **)(&tmp));
		curr = curr->next;
	}
}
