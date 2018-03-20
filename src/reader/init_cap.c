/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/20 15:11:59 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	init_cap_arrow(char b, int i, int (*f)())
{
	if (f == NULL)
		return (0);
	g_handleinput[i].cap[0] = 27;
	g_handleinput[i].cap[1] = 91;
	g_handleinput[i].cap[2] = b;
	g_handleinput[i].cap[3] = 0;
	g_handleinput[i].cap[4] = 0;
	g_handleinput[i].cap[5] = 0;
	g_handleinput[i].cap[6] = 0;
	g_handleinput[i].cap[7] = 0;
	g_handleinput[i].f = f;
	return (1);
}

static int	init_cap_shift(char b, int i, int (*f)())
{
	if (f == NULL)
		return (0);
	g_handleinput[i].cap[0] = 27;
	g_handleinput[i].cap[1] = 91;
	g_handleinput[i].cap[2] = 49;
	g_handleinput[i].cap[3] = 59;
	g_handleinput[i].cap[4] = 50;
	g_handleinput[i].cap[5] = b;
	g_handleinput[i].cap[6] = 0;
	g_handleinput[i].cap[7] = 0;
	g_handleinput[i].f = f;
	return (1);
}

static int	init_cap_esc(char b, int i, int (*f)())
{
	if (f == NULL)
		return (0);
	g_handleinput[i].cap[0] = 27;
	g_handleinput[i].cap[1] = 91;
	g_handleinput[i].cap[2] = 51;
	g_handleinput[i].cap[3] = b;
	g_handleinput[i].cap[4] = 0;
	g_handleinput[i].cap[5] = 0;
	g_handleinput[i].cap[6] = 0;
	g_handleinput[i].cap[7] = 0;
	g_handleinput[i].f = f;
	return (1);
}

static int	init_cap_del(char b, int i, int (*f)())
{
	if (f == NULL)
		return (0);
	g_handleinput[i].cap[0] = b;
	g_handleinput[i].cap[1] = 0;
	g_handleinput[i].cap[2] = 0;
	g_handleinput[i].cap[3] = 0;
	g_handleinput[i].cap[4] = 0;
	g_handleinput[i].cap[5] = 0;
	g_handleinput[i].cap[6] = 0;
	g_handleinput[i].cap[7] = 0;
	g_handleinput[i].f = f;
	return (1);
}

int			init_cap(void)
{
	init_tab();
	init_cap_arrow(65, K_UP, &move_updown);
	init_cap_arrow(66, K_DOWN, &move_updown);
	init_cap_arrow(67, K_RIGHT, &move_right);
	init_cap_arrow(68, K_LEFT, &move_left);
	init_cap_arrow(70, K_END, &move_end);
	init_cap_arrow(72, K_HOME, &move_home);
	init_cap_shift(65, K_PUP, &move_sup);
	init_cap_shift(66, K_PDOWN, &move_sdown);
	init_cap_shift(67, K_PRIGHT, &move_sright);
	init_cap_shift(68, K_PLEFT, &move_sleft);
	init_cap_esc(126, K_DELR, &handle_del_right);
	init_cap_del(127, K_DEL, &handle_del);
	init_cap_del(4, K_CTRLD, &ft_quit);
	init_cap_del(28, K_QUIT, &ft_quit);
	init_cap_del(11, K_CUT, &cut_list);
	init_cap_del(12, K_YANK, &paste_list);
	init_cap_del(9, K_TAB, &printlvl);
	return (0);
}
