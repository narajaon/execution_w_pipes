/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:10:15 by awyart            #+#    #+#             */
/*   Updated: 2017/12/14 17:11:11 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void			ft_dlist_repl(t_dlist *node, t_dlist *chain)
{
	t_dlist				*tmp;
	t_dlist				*last;

	ft_dlist_swap(node, chain);
	tmp = chain->next == NULL ? NULL : chain->next;
	ft_dlist_free(&chain, &ft_memdel);
	if (tmp != NULL)
	{
		last = ft_dlist_last(tmp);
		last->next = node->next;
		node->next = tmp;
	}
}

static void		change_own(t_dlist *a1, t_dlist *a2, t_dlist *b1, t_dlist *b2)
{
	a1->next = b1->next;
	a2->prev = b2->prev;
	b1->next = b2;
	b2->prev = b1;
}

static void		swap_own(t_dlist *a1, t_dlist *a2, t_dlist *b1, t_dlist *b2)
{
	t_dlist		*c1;
	t_dlist		*c2;

	c1 = a1->next;
	c2 = a2->prev;
	a1->next = b1->next;
	a2->prev = b2->prev;
	b1->next = c1;
	b2->prev = c2;
}

void			ft_dlist_repl_mult(t_dlist *begin, t_dlist *end, t_dlist *chain)
{
	t_dlist		*last;

	if (begin == end)
	{
		ft_dlist_repl(begin, chain);
		return ;
	}
	last = ft_dlist_last(chain);
	ft_dlist_swap(begin, chain);
	ft_dlist_swap(end, last);
	if (begin->next == end && chain->next == last)
		return ;
	else if (begin->next == end)
		change_own(begin, end, chain, last);
	else if (chain->next == last)
		change_own(chain, last, begin, end);
	else
		swap_own(begin, end, chain, last);
	ft_dlist_clear(&chain, &ft_memdel);
}
