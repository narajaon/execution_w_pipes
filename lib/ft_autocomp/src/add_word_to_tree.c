/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word_to_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:43:13 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:44:08 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/levenshtein.h"

void		check_child_list(t_dlist **child, t_dlist *word)
{
	t_lev	*new;
	t_lev	*cur_char;
	t_dlist	*tmp;

	new = NULL;
	tmp = *child;
	while (tmp != NULL && word != NULL)
	{
		new = tmp->content;
		cur_char = word->content;
		if (new->content == cur_char->content)
		{
			if (word->next == NULL)
				break ;
			check_child_list(&new->child, word->next);
			return ;
		}
		tmp = tmp->next;
	}
	if (word)
	{
		add_to_child(&tmp, word);
		ft_hlstadd(child, tmp);
	}
}

void		add_to_child(t_dlist **child, t_dlist *word)
{
	t_lev	*new;

	new = NULL;
	if (word == NULL)
		return ;
	if (*child == NULL)
	{
		new = word->content;
		*child = ft_hlstnew(new);
		new = (*child)->content;
		add_to_child(&new->child, word->next);
	}
	else if (*child != NULL)
		check_child_list(child, word);
}
