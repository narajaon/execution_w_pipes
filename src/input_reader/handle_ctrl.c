/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 21:54:18 by awyart            #+#    #+#             */
/*   Updated: 2017/12/14 16:47:00 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		move_left_word(t_dlist_wrap *wrap, t_sh *sh)
{
	int ret;
	int count;

	ret = 1;
	count = 0;
	ret = move_left(wrap, sh);
	while (ret != 0 && (!(ft_lisspace(wrap->cursor))))
	{
		ret = move_left(wrap, sh);
		count++;
	}
	wrap->last_mov = 0;
	return (count);
}

int		move_right_word(t_dlist_wrap *wrap, t_sh *sh)
{
	t_chr	*schar;
	int		ret;
	int		count;

	ret = 1;
	count = 0;
	schar = wrap->cursor->content;
	while (ret != 0 && ft_lisspace(wrap->cursor))
	{
		ret = move_right(wrap, sh);
		count++;
	}
	wrap->last_mov = 0;
	return (count);
}

int		move_up_ctrl(t_dlist_wrap *wrap, t_sh *sh)
{
	int y;
	int ret;

	y = sh->term.win.ws_col + 1;
	ret = 1;
	while (--y)
	{
		if (ret == 0)
			break ;
		ret = move_left(wrap, sh);
		ft_refresh_line(wrap, sh);
	}
	wrap->last_mov = 0;
	return (1);
}

int		move_down_ctrl(t_dlist_wrap *wrap, t_sh *sh)
{
	int y;
	int ret;

	y = sh->term.win.ws_col + 1;
	ret = 1;
	while (--y)
	{
		if (ret == 0)
			break ;
		ret = move_right(wrap, sh);
		ft_refresh_line(wrap, sh);
	}
	wrap->last_mov = 0;
	return (1);
}
