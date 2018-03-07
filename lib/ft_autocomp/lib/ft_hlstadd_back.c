/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:43:13 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:43:34 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/levenshtein.h"

void		ft_hlstadd_back_void(t_dlist **alst, void *new)
{
	t_dlist		*tmp;
	t_dlist		*node;

	tmp = *alst;
	node = ft_hlstnew_void(new);
	if (*alst == NULL)
	{
		*alst = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
}

void		ft_hlstadd_back(t_dlist **alst, t_dlist *new)
{
	t_dlist	*tmp;

	tmp = *alst;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
