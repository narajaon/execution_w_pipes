/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printcolor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 15:37:58 by awyart            #+#    #+#             */
/*   Updated: 2018/03/09 18:45:58 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void 	ft_printcolor(t_dlist *head)
{
	t_dlist *list;

	list = head;
	dprintf(g_fd, "debut\n");
	while (list != NULL)
	{
		check_norm(&list);
		dprintf(g_fd, "norm checked\n");
	}
}