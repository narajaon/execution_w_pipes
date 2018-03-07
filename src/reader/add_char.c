/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:40:42 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_dlist	*create_node(char c)
{
	t_dlist	*tmp;
	t_chr	*schar;

	schar = ft_memalloc(sizeof(t_chr));
	tmp = ft_dlist_create((void *)(schar));
	if (schar == NULL || tmp == NULL)
	{
		ft_memdel((void **)&schar);
		ft_memdel((void **)&tmp);
		return (NULL);
	}
	schar->c = c;
	schar->is_escaped = '0';
	return (tmp);
}

t_dlist			*cur_list(t_dlist_wrap *wrap)
{
	int		pos;
	t_dlist	*list;

	if (wrap == NULL || wrap->head == NULL)
		return (NULL);
	list = wrap->head;
	pos = wrap->pos;
	while (--pos && list != NULL)
	{
		if (pos <= 0)
			break ;
		list = list->next;
	}
	return (list);
}

static int		add_in_list(t_dlist_wrap *wrap, t_dlist *new)
{
	t_dlist	*list;
	t_dlist	*next;

	if (wrap->pos == 0)
	{
		list = wrap->head;
		new->next = list;
		new->prev = NULL;
		list->prev = new;
		wrap->head = new;
	}
	else
	{
		list = cur_list(wrap);
		if (!list)
			return (0);
		next = list->next;
		if (next != NULL)
			next->prev = new;
		list->next = new;
		new->next = next;
		new->prev = list;
	}
	return (1);
}

int				handle_char(char buf[3], t_dlist_wrap *wrap)
{
	t_dlist *new;

	new = NULL;
	if ((new = create_node(buf[0])) == NULL)
		return (-1);
	if (wrap->head == NULL)
	{
		wrap->head = new;
		wrap->pos = 1;
		wrap->size = 1;
	}
	else
	{
		if (add_in_list(wrap, new))
		{
			wrap->pos++;
			wrap->size++;
		}
	}
	return (1);
}
