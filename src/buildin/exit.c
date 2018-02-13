/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 07:46:03 by awyart            #+#    #+#             */
/*   Updated: 2018/02/13 14:42:09 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	kill(g_cur_pid, SIGQUIT);
	return (0);
}
