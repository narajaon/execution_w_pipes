/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/20 15:11:04 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_printable(char buf[8])
{
	char c;

	c = buf[0];
	if (c < 32 || c > 125)
		return (0);
	if (buf[1] != 0 || buf[2] != 0 || buf[3] != 0)
		return (0);
	return (1);
}

int	is_break(char buf[8])
{
	if (buf[0] == 13 && buf[1] == 0 && buf[2] == 0 && buf[3] == 0)
		return (1);
	if (buf[0] == 10 && buf[1] == 0 && buf[2] == 0 && buf[3] == 0)
		return (1);
	return (0);
}

int	is_updown(char buf[8])
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66 && buf[3] == 0)
		return (1);
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65 && buf[3] == 0)
		return (1);
	return (0);
}
