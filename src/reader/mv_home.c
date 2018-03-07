/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:41:10 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	move_end(t_dlist_wrap *wrap)
{
	if (wrap->pos < 0 || wrap->pos >= wrap->size)
		return (0);
	wrap->pos = wrap->size;
	return (1);
}

int	move_home(t_dlist_wrap *wrap)
{
	if (wrap->pos <= 0)
		return (0);
	wrap->pos = 0;
	return (1);
}
