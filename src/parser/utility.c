/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:53:03 by awyart            #+#    #+#             */
/*   Updated: 2017/12/14 17:59:10 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char *spe_strdup(t_token *token)
{
	static char buf[1024];
	t_dlist *list;
	t_chr	*schar;
	int i;

	i = 0;
	list = token->first_letter;
	while (list != NULL)
	{
		schar = list->content;
		buf[i++] = schar->c;
		if (list == token->last_letter)
			break ;
		list = list->next;
	}
	buf[i] = '\0';
	return (ft_strdup(buf));
}