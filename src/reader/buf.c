/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:40:44 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_printable(char buf[3])
{
	char c;

	c = buf[0];
	if (c < 32 || c > 125)
		return (0);
	if (buf[1] != 0 || buf[2] != 0)
		return (0);
	return (1);
}

int	is_break(char buf[3])
{
	if (buf[0] == 13 && buf[1] == 0 && buf[2] == 0)
		return (1);
	if (buf[0] == 10 && buf[1] == 0 && buf[2] == 0)
		return (1);
	return (0);
}

int	is_updown(char buf[3])
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		return (1);
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		return (1);
	return (0);
}
