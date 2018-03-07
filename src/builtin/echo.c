/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:42:20 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:39:31 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			ft_echo(t_sh *sh, char **av)
{
	int		i;

	i = 1;
	(void)sh;
	while (av[i] != NULL)
	{
		ft_putstr(av[i++]);
		if (av[i] != NULL)
			ft_putstr(" ");
	}
	ft_putstr("\n");
	return (0);
}
