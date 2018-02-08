/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 19:16:02 by awyart            #+#    #+#             */
/*   Updated: 2018/01/26 11:12:03 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int 	ft_print_lexinput(t_dlist **list)
{
	t_dlist *tmp = NULL;
	int 	count;
	t_chr	*schar = NULL;

	tmp = *list;
	count = 0;
	dprintf(g_fd, "\n Liste fournie au lexer: \n");
	while (tmp != NULL)
	{
		schar = tmp->content;
		dprintf(g_fd, "%c", schar->c);
		tmp = tmp->next;
		count++;
	}
	return (count);
}

int 	ft_print_lexoutput(t_token **list)
{
	t_token *tmp;
	t_dlist *begin;
	int 	count;
	t_chr	*schar = NULL;

	tmp = *list;
	count = 0;
	dprintf(g_fd, "\n Sortie au lexer: \n");
	while (tmp != NULL)
	{
		begin = tmp->first_letter;
		dprintf(g_fd, "|");
		while (begin != NULL && begin != tmp->last_letter)
		{
			schar = begin->content;
			if (schar->is_escaped == '1')
				dprintf(g_fd, "\033[0;7;37;40m%c\033[0;0;0;0m", schar->c);
			else
				dprintf(g_fd, "%c", schar->c);
			begin = begin->next;
		}
		if (begin)
		{
			schar = begin->content;
			if (schar->is_escaped == '1')
				dprintf(g_fd, "\033[0;7;37;40m%c\033[0;0;0;0m", schar->c);
			else
				dprintf(g_fd, "%c", schar->c);
		}
		dprintf(g_fd, "|<%d>->", tmp->e_type);
		tmp = tmp->next;
		count++;
	}
	dprintf(g_fd, " NULL\n");
	return (count);
}
