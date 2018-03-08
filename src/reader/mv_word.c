/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/08 14:02:35 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	sizerightword(t_dlist *list)
{
	t_chr	*schar;
	int		count;

	count = 0;
	if (list == NULL)
		return (0);
	schar = list->content;
	while (ft_isspace(schar->c) == 0)
	{
		count++;
		list = list->next;
		if (list == NULL)
			break ;
		schar = list->content;
	}
	while (ft_isspace(schar->c))
	{
		count++;
		list = list->next;
		if (list == NULL)
			break ;
		schar = list->content;
	}
	return (count);
}

static int	sizeleftword(t_dlist *list)
{
	t_chr	*schar;
	int		count;

	count = 0;
	if (list == NULL)
		return (0);
	schar = list->content;
	while (ft_isspace(schar->c))
	{
		count++;
		list = list->prev;
		if (list == NULL)
			break ;
		schar = list->content;
	}
	while (!ft_isspace(schar->c))
	{
		count++;
		list = list->prev;
		if (list == NULL)
			break ;
		schar = list->content;
	}
	return (count);
}

int			move_sright(t_dlist_wrap *wrap)
{
	int		i;
	t_dlist	*list;

	if (wrap->tmp != NULL)
		return (0);
	list = cur_list(wrap);
	if (list)
		list = list->next;
	i = sizerightword(list);
	if (i == 0)
		return (0);
	if (wrap->pos == 0)
		i++;
	wrap->pos += i;
	if (wrap->pos >= wrap->size)
		wrap->pos = wrap->size;
	return (1);
}

int			move_sleft(t_dlist_wrap *wrap)
{
	int	i;

	if (wrap->tmp != NULL)
		return (0);
	i = sizeleftword(cur_list(wrap));
	if (i == 0)
		return (0);
	wrap->pos -= i;
	if (wrap->pos <= 0)
		wrap->pos = 0;
	return (1);
}
