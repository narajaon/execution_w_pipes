/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 07:46:03 by awyart            #+#    #+#             */
/*   Updated: 2018/02/16 14:53:38 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int		ft_exit(t_sh *sh, char **av)
{
//	if (av[1] == NULL)
//		exit(sh->ret);
	(void)sh;
	if (av[1] != NULL && av[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	tcsetattr(0, TCSANOW, &(sh->term.prev_term));
//	NBR(g_cur_pid);
	kill(g_cur_pid, SIGQUIT);
	exit(0);
	return (0);
}
