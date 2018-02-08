/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_swap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 17:55:12 by awyart            #+#    #+#             */
/*   Updated: 2017/12/14 17:10:43 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void				ft_dlist_swap(t_dlist *lhs, t_dlist *rhs)
{
	void			*content;

	content = lhs->content;
	lhs->content = rhs->content;
	rhs->content = content;
}
