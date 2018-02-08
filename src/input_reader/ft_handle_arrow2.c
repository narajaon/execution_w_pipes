/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_arrow2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 22:46:01 by awyart            #+#    #+#             */
/*   Updated: 2017/12/14 16:41:36 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int						move_end(t_dlist_wrap *wrap, t_sh *sh)
{
	int ret;

	ret = 1;
	while (1)
	{
		if (ret == 0)
			break ;
		ret = move_right(wrap, sh);
		ft_refresh_line(wrap, sh);
	}
	wrap->last_mov = END;
	return (1);
}

int						move_begin(t_dlist_wrap *wrap, t_sh *sh)
{
	int ret;

	ret = 1;
	while (1)
	{
		if (ret == 0)
			break ;
		ret = move_left(wrap, sh);
		ft_refresh_line(wrap, sh);
	}
	wrap->last_mov = BEGIN;
	return (1);
}
