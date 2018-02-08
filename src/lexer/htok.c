/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htok.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 18:03:03 by awyart            #+#    #+#             */
/*   Updated: 2018/01/10 17:16:22 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_listok(t_dlist *list)
{
	char	c;
	t_chr	*schar;

	if (list != NULL)
	{
		schar = list->content;
		c = schar->c;
		if (schar->is_escaped == '1')
			return (0);
		if (c == '|' || c == '&' || c == '<')
			return (1);
		if (c == '>' || c == ';')
			return (1);
	}
	return (0);
}

int		ft_lisspace(t_dlist *list)
{
	char	c;
	t_chr	*schar;

	schar = list->content;
	c = schar->c;
	if (c == '\n' || c == ' ' || c == '\v'
		|| c == '\r' || c == '\f' || c == '\t')
		return (1);
	return (0);
}

char	ft_lisquote(t_dlist *list, char etalon)
{
	char	c;
	t_chr	*schar;

	schar = list->content;
	c = schar->c;
	if (etalon == 0)
	{
		if (c == '\"' || c == '\'')
			return (c);
	}
	else
	{
		if (c == etalon)
			return (1);
	}
	return (0);
}

int		ft_listop(t_dlist *list)
{
	if (ft_lisspace(list) || ft_listok(list))
		return (1);
	return (0);
}
