/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:43:13 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:41:53 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char		**ft_list_to_tab(t_dlist *list)
{
	char	**av;
	int		lst_size;
	int		i;

	i = 0;
	lst_size = hlst_size(list);
	av = (char **)malloc(sizeof(char *) * (lst_size + 1));
	while (list)
	{
		av[i++] = list->content;
		list = list->next;
	}
	av[i] = NULL;
	return (av);
}
