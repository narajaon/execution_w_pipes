/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 07:46:03 by awyart            #+#    #+#             */
/*   Updated: 2018/02/21 17:23:13 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int		ft_exit(t_sh *sh, char **av)
{
	(void)sh;
	if (av[1] != NULL && av[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (av[1] == NULL)
		ft_quit();
	exit(ft_atoi(av[1]));
	return (0);
}
