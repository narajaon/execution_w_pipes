/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:43:13 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:43:37 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/levenshtein.h"

t_dlist		*ft_hlstnew(t_lev *new)
{
	t_dlist	*child;

	if ((child = (t_dlist *)malloc(sizeof(t_dlist))) == NULL)
		return (NULL);
	child->content = new;
	child->prev = NULL;
	child->next = NULL;
	return (child);
}

t_dlist		*ft_hlstnew_void(void *new)
{
	t_dlist	*child;

	if ((child = (t_dlist *)malloc(sizeof(t_dlist))) == NULL)
		return (NULL);
	child->content = new;
	child->prev = NULL;
	child->next = NULL;
	return (child);
}
