/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_delone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 15:52:22 by awyart            #+#    #+#             */
/*   Updated: 2017/12/11 16:06:42 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlist_delone(t_dlist **to_del)
{
	if (!to_del || !(*to_del))
		return ;
	if ((*to_del)->prev)
		(*to_del)->prev->next = (*to_del)->next;
	if ((*to_del)->next)
		(*to_del)->next->prev = (*to_del)->prev;
	(*to_del)->prev = NULL;
	(*to_del)->next = NULL;
	if ((*to_del)->content)
		free((*to_del)->content);
	(*to_del)->content = NULL;
	free((*to_del));
	*to_del = NULL;
}
