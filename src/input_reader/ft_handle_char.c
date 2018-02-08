/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 11:50:33 by awyart            #+#    #+#             */
/*   Updated: 2017/12/20 22:50:55 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_dlist		*create_node(char c)
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

static int	ft_new_wrapper(t_dlist *new, t_dlist_wrap *wrap)
{
	wrap->head = new;
	wrap->last = wrap->head;
	wrap->cursor = NULL;
	return (1);
}

static int	ft_add_list(t_dlist *new, t_dlist_wrap *wrap)
{
	new->prev = wrap->last;
	wrap->last->next = new;
	wrap->last = new;
	return (1);
}

static int	ft_insert_inlist(t_dlist *new, t_dlist_wrap *wrap)
{
	t_dlist *cursor;

	cursor = wrap->cursor;
	new->next = cursor;
	cursor->prev = new;
	new->prev = wrap->last;
	if (wrap->last != NULL)
		wrap->last->next = new;
	else
		wrap->head = new;
	wrap->cursor = new->next;
	wrap->last = new;
	return (1);
}

int 		ft_print_dlist(t_dlist *list)
{
	t_chr *schar = NULL;
	int ret;

	ret = 0;
	while (list != NULL)
	{
		schar = list->content;
		write(STDOUT_FILENO, &schar->c, 1);
		list = list->next;
		ret++;
	}
	return (ret);
}


int			handle_char(char c, t_dlist_wrap *wrap, t_sh *sh)
{
	t_dlist	*new;

	new = NULL;
	if ((new = create_node(c)) == NULL)
		return (-1);
	if (wrap->head == NULL || wrap->head->content == NULL)
	{
		if (ft_new_wrapper(new, wrap) == 0)
			return (0);
	}
	else if (wrap->cursor == NULL || wrap->cursor->content == NULL)
	{
		if (ft_add_list(new, wrap) == 0)
			return (0);
	}
	else
	{
		if (ft_insert_inlist(new, wrap) == 0)
			return (0);
	}
	wrap->pos++;
	if (wrap->cursor == NULL)
		wrap->last_mov = ADD_END;
	else
		wrap->last_mov = ADD;
	sh->offset = 0;
	return (1);
}
