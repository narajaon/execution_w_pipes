/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:46:37 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/autocompletion.h"

const void		*g_hist_manip[IR_SIZE] = {&history_down, &history_up, 0, 0};

void		add_to_path(char *path, char *file_name)
{
	if (*path != 0)
		ft_strcat(path, "/");
	ft_strcat(path, file_name);
}

void		history_init(t_hist *hstruct)
{
	ft_strcpy(hstruct->hist_path, HISTORY);
	hstruct->history_root = history_to_list(hstruct->history_fd);
	hstruct->cur_branch = NULL;
	hstruct->branch_root = NULL;
}

void		remove_zero(t_dlist **dlist)
{
	t_dlist		*list;
	t_dlist		*prev;
	t_chr		*chr;

	chr = NULL;
	prev = NULL;
	list = *dlist;
	while (list)
	{
		prev = list->prev;
		chr = list->content;
		if (chr->c == '\0')
		{
			if (prev != NULL)
			{
				prev->next = NULL;
				free(list->content);
				free(list);
				list = NULL;
			}
			break ;
		}
		list = list->next;
	}
}

void		print_chr(t_dlist *lst)
{
	t_chr		*chr;

	while (lst)
	{
		chr = lst->content;
		ft_putchar(chr->c);
		lst = lst->next;
	}
}

t_dlist		*history_handler(int event, t_dlist *input, t_hist *hstruct)
{
	t_dlist		*(*search_hist)(t_dlist *, t_dlist *, t_dlist *);
	t_dlist		*tmp;

	search_hist = g_hist_manip[event];
	hstruct->cur_branch = search_hist(input, hstruct->cur_branch,
			hstruct->history_root);
	if (hstruct->branch_root == NULL)
		hstruct->branch_root = hstruct->cur_branch;
	if (hstruct->cur_branch != NULL)
	{
		tmp = hstruct->cur_branch->content;
		remove_zero(&tmp);
	}
	return (hstruct->cur_branch);
}
