/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_autocmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:43:13 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:44:20 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/levenshtein.h"

void		free_lev_tree(t_dlist **data_base)
{
	t_dlist			*branch;
	t_dlist			*child;
	t_lev			*node;
	char			*c;

	node = NULL;
	if (data_base != NULL)
	{
		branch = *data_base;
		while (branch)
		{
			node = branch->content;
			child = node->child;
			if (branch->next != NULL)
				free_lev_tree(&branch->next);
			free(node);
			free(branch);
			branch = child;
		}
	}
}

void		free_autocmp_res(t_dlist **data_base)
{
	t_dlist		*to_free;
	t_dlist		*content;

	to_free = *data_base;
	while (to_free)
	{
		content = to_free->content;
		free_hlist(&content);
		free(to_free);
		to_free = to_free->next;
	}
}
