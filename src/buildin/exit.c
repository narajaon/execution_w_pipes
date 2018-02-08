/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 07:46:03 by awyart            #+#    #+#             */
/*   Updated: 2018/02/02 16:40:32 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_exit(t_sh *sh, char **av)
{
	if (av[1] == NULL)
		exit(sh->ret);
	if (av[1] != NULL && av[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	exit(ft_atoi(av[1]));
	return (0);
}
