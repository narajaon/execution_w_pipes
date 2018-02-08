/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 17:55:12 by awyart            #+#    #+#             */
/*   Updated: 2017/12/14 17:10:18 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

t_dlist				*ft_dlist_create(void *content)
{
	t_dlist			*ret;

	if ((ret = (t_dlist *)ft_memalloc(sizeof(t_dlist))) == NULL)
		return (NULL);
	ret->content = content;
	return (ret);
}
