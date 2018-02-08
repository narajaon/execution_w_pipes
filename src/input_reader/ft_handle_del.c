/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:28:02 by awyart            #+#    #+#             */
/*   Updated: 2017/12/14 21:06:25 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// int				handle_del(t_dlist_wrap *wrap, t_sh *sh)
// {
// 	t_dlist *todel;

// 	if (!wrap || !wrap->head || !wrap->last)
// 		return (-1);
// 	todel = wrap->last;
// 	clearline(wrap, sh);
// 	if (todel->prev)
// 		todel->prev->next = todel->next;
// 	if (todel->next)
// 		todel->next->prev = todel->prev;
// 	wrap->last = todel->prev;
// 	todel->prev = NULL;
// 	todel->next = NULL;
// 	ft_dlist_free(&todel, ft_memdel);
// 	if (wrap->head == NULL || wrap->head->content == NULL)
// 		wrap->head = wrap->cursor;
// 	wrap->pos--;
// 	ft_print_list(wrap, sh);
// 	return (1);
// }

// int				handle_del_right(t_dlist_wrap *wrap, t_sh *sh)
// {
// 	t_dlist *list;
// 	int offset;

// 	if ((!wrap || !wrap->head || !wrap->cursor))
// 		return (-1);
// 	offset = clearline(wrap, sh);
// 	list = wrap->cursor;
// 	wrap->cursor = wrap->cursor->next;
// 	ft_dlist_delone(&list);
// 	if (wrap->head == NULL || wrap->head->content == NULL)
// 		wrap->head = wrap->cursor;
// 	ft_print_list(wrap, sh);
// 	ft_reset_cursor(offset, wrap, sh);
// 	return (1);
// }


int				handle_del(t_dlist_wrap *wrap, t_sh *sh)
{
	t_dlist *todel;

	if (!wrap || !wrap->head || !wrap->last)
 		return (-1);
 	todel = wrap->last;
 	if (todel->prev)
		todel->prev->next = todel->next;
	if (todel->next)
		todel->next->prev = todel->prev;
	wrap->last = todel->prev;
	todel->prev = NULL;
	todel->next = NULL;
	ft_dlist_free(&todel, ft_memdel);
   	wrap->pos--;
 	if (wrap->pos == 0)
 		wrap->head = wrap->cursor;
 	wrap->last_mov = DEL;
 	sh->offset = 0;
 	return (1);
}

int				handle_del_right(t_dlist_wrap *wrap, t_sh *sh)
{
	t_dlist *todel;
	int test = 0;

	if ((!wrap || !wrap->head || !wrap->cursor))
		return (-1);
	if (wrap->cursor == wrap->head)
		test = 1;
	todel = wrap->cursor;
	if (todel->prev)
		todel->prev->next = todel->next;
	if (todel->next)
		todel->next->prev = todel->prev;
	wrap->cursor = wrap->cursor->next;
	todel->prev = NULL;
	todel->next = NULL;
	ft_dlist_free(&todel, ft_memdel);
	if (test == 1)
		wrap->head = wrap->cursor;
	wrap->last_mov = DEL;
	sh->offset = 0;
	return (1);
}