/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 17:55:12 by awyart            #+#    #+#             */
/*   Updated: 2017/12/14 17:10:34 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

t_dlist				*ft_dlist_insert(t_dlist *curr, t_dlist *chain)
{
	t_dlist			*last;

	last = ft_dlist_last(chain);
	last->next = curr->next;
	curr->next = chain;
	return (last);
}
