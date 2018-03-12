/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:11:35 by awyart            #+#    #+#             */
/*   Updated: 2018/03/12 16:33:19 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int is_dlist_space(t_dlist *list)
{
	t_chr *schar;

	if (list == NULL)
		return (0);
	schar = list->content;
	return (ft_isspace(schar->c));
}

int is_dlist_word(t_dlist *list)
{
	t_chr *schar;

	if (list == NULL)
		return (0);
	schar = list->content;
	return (!(ft_isspace(schar->c)));
}

int is_dlist_opt(t_dlist *list)
{
	t_chr *schar;

	if (list == NULL)
		return (0);
	schar = list->content;
	if (schar->c == '-')
		return (1);
	return (0);
}

int is_dlist_red(t_dlist *list)
{
	t_chr *schar;

	if (list == NULL)
		return (0);
	schar = list->content;
	if (schar->c == '<' || schar->c == '>' || schar->c == '|'
			|| schar->c == ';' || schar->c == '&')
		return (1);
	return (0);
}