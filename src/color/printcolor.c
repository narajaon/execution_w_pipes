/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printcolor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 15:37:58 by awyart            #+#    #+#             */
/*   Updated: 2018/03/20 15:06:07 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_printcolor(t_dlist *head)
{
	t_dlist *list;

	list = head;
	while (list != NULL)
		check_norm(&list);
}
