/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hl_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:43:13 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:43:39 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/levenshtein.h"

t_dlist		*hl_list_dup(t_dlist *node)
{
	t_dlist		*list;
	t_dlist		*list_ptr;
	t_dlist		*tmp;

	tmp = node;
	if (!(list = hl_node_dup(tmp, sizeof(t_dlist))))
		return (NULL);
	list_ptr = list;
	if (tmp != NULL)
	{
		tmp = tmp->next;
		list = list->next;
	}
	while (tmp != NULL)
	{
		list = hl_node_dup(tmp, sizeof(t_dlist));
		list = list->next;
		tmp = tmp->next;
	}
	return (list_ptr);
}

t_dlist		*hl_node_dup(t_dlist *node, size_t size)
{
	t_dlist		*dup;

	if (node == NULL)
		return (NULL);
	if ((dup = (t_dlist *)malloc(sizeof(t_dlist))) == NULL)
		return (NULL);
	dup->content = ft_memalloc(size);
	ft_memcpy(dup->content, node->content, size);
	dup->next = NULL;
	dup->prev = NULL;
	return (dup);
}

t_dlist		*ft_dlist_dup(t_dlist *src, size_t size)
{
	t_dlist		*dup;
	t_dlist		*new;

	if (src == NULL)
		return (NULL);
	dup = NULL;
	while (src != NULL)
	{
		new = hl_node_dup(src, size);
		ft_hlstadd_back(&dup, new);
		src = src->next;
	}
	return (dup);
}
