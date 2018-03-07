/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_branch_to_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:43:13 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:44:05 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/levenshtein.h"

void		add_branch_to_input(t_dlist **input, t_dlist *branch)
{
	t_lev		*new;
	t_dlist		*tmp;

	if (branch == NULL)
		return ;
	if (*input == NULL)
	{
		tmp = *input;
		while (branch)
		{
			new = branch->content;
			ft_hlstadd_back(input, branch);
			branch = new->child;
		}
	}
	else
		add_branch_to_input(&(*input)->next, branch);
}
