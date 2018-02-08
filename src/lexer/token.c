/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:04:28 by awyart            #+#    #+#             */
/*   Updated: 2018/01/10 17:16:33 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_token		*ft_create_token(t_dlist *line)
{
	t_token	*token;

	if ((token = (t_token *)malloc(sizeof(t_token))) == NULL)
		return (NULL);
	token->first_letter = line;
	token->last_letter = NULL;
	token->next = NULL;
	token->e_type = NEW;
	return (token);
}

int			ft_handle_word(t_dlist **list)
{
	char	c;

	while (*list != NULL)
	{
		if (ft_listop(*list))
			break ;
		if ((c = ft_lisquote(*list, 0)) != 0)
		{
			*list = (*list)->next;
			while (list != NULL && ft_lisquote(*list, c) == 0)
				*list = (*list)->next;
		}
		*list = (*list)->next;
	}
	return (1);
}

static int	ft_handle_oth(int e, t_dlist **list)
{
	if (e == IO_NUMBER || e == PIPE || e == AND || e == OR
		|| e == SEMICOL || e == BSLASH || e == LREDIR || e == RSREDIR)
	{
		return (1);
	}
	if (e == NEWLINE || e == DPIPE || e == LAND || e == LOR
		|| e == DSEMICOL || e == RDREDIR)
	{
		*list = (*list)->next;
		return (2);
	}
	return (0);
}

static void	ft_add_token(t_token *new, t_token **token)
{
	t_token *tmp;

	tmp = *token;
	if (tmp == NULL)
		*token = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int			ft_get_token(t_token *token, t_token **ttoken)
{
	t_dlist	*list;
	t_chr	*schar;

	list = token->first_letter;
	schar = list->content;
	token->e_type = ft_detect_type(list);
	if (token->e_type == WORD)
	{
		ft_handle_word(&list);
		if (ft_listok(list))
			list = list->prev;
	}
	else
		ft_handle_oth(token->e_type, &list);
	while (list != NULL && ft_lisspace(list))
		list = list->prev;
	token->last_letter = list;
	ft_add_token(token, ttoken);
	return (1);
}
