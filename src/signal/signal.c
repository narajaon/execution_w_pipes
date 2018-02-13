/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:03:12 by awyart            #+#    #+#             */
/*   Updated: 2018/02/13 14:54:20 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool		jump_loop(void)
{
	if (g_loop == FALSE)
	{
		ft_putchar('\n');
		g_loop = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

void		ft_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		// need to free stuff here
		ft_prompt(g_sh);
	}
}

void		ft_getsignal(void)
{
	signal(SIGINT, &ft_signal);
}
