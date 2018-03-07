/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:41:07 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	wrap->pos--;
	return (1);
}
