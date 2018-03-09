/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tok.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:33:01 by awyart            #+#    #+#             */
/*   Updated: 2018/03/09 16:33:16 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int is_token(t_dlist *list)
{
	t_chr *schar;

	if (list == NULL)
		return (0);
	schar = list->content;
	if (schar->c == '<' || schar->c == '>' || schar->c == ';')
		return (1);
	if (schar->c == '&' || schar->c == '|')
		return (1);
	return (0);
}

int is_token_redir(t_dlist *list)
{
	t_chr *schar;

	if (list == NULL)
		return (0);
	schar = list->content;
	if (schar->c == '<' || schar->c == '>')
		return (1);
	if (ft_isdigit(schar->c))
	{
		list = list->next;
		if (list && (schar = list->content))
		{
			if (schar->c == '<' || schar->c == '>')
				return (1);
		}
	}
	return (0);
}
