/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 18:11:55 by awyart            #+#    #+#             */
/*   Updated: 2018/03/20 18:18:01 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_color(t_sh *sh, char **av)
{
	sh->color = ((sh->color == 1) ? 0 : 1);
	(void)av;
	return (1);
}
