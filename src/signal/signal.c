/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:03:12 by awyart            #+#    #+#             */
/*   Updated: 2018/02/21 18:37:14 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		ft_signal(int sig)
{
	if (sig == SIGINT)
	{
		NBR(g_cur_pid);
		NBR(g_shlvl);
	//	ft_putstr("\n");
		// need to free stuff here
	}
}

void		ft_getsignal(void)
{
	signal(SIGINT, &ft_signal);
}
