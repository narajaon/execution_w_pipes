/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 17:55:12 by awyart            #+#    #+#             */
/*   Updated: 2017/12/14 17:10:46 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

char			*ft_dlist_to_str(t_dlist *begin, t_dlist *end)
{
	char		*str;
	size_t		len;
	size_t		pos;

	len = ft_dlist_len(begin, end);
	pos = 0;
	if ((str = (char *)ft_memalloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	while (begin != end)
	{
		str[pos] = *((char *)(begin->content));
		begin = begin->next;
		pos++;
	}
	return (str);
}
