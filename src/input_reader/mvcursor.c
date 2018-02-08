/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvcursor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:22:40 by awyart            #+#    #+#             */
/*   Updated: 2018/01/22 13:22:30 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			ft_printlist(t_dlist_wrap *wrap, t_sh *sh)
{
	t_dlist 	*list;
	t_chr		*schar;

	list = wrap->head;
	dprintf(g_fd, "\33[H\33[2JLIST \n");
	while (list != NULL)
	{
		schar = list->content;
		if (list != wrap->cursor)
			dprintf(g_fd, "%c>", schar->c);
		else
			dprintf(g_fd, "\033[0;7;37;40m %c \033[0;0;0;0m->", schar->c);
		list = list->next;
	}
	dprintf(g_fd,"NULL\n");
	if (wrap)
	{
		if (wrap->head)
		{
			schar = wrap->head->content;
			dprintf(g_fd, " head <%c>", schar->c);
		}
		if (wrap->last)
		{
			schar = wrap->last->content;
			dprintf(g_fd, "last <%c>", schar->c);
		}
		if (wrap->cursor)
		{
			schar = wrap->cursor->content;
			dprintf(g_fd, " cursor <%c>", schar->c);
		}
		dprintf(g_fd, "\nraw = <%d> g_tmp = <%d> g_tmp2 = <%d>", sh->term.win.ws_row, g_tmp, g_tmp2);
		dprintf(g_fd, "\ncol = <%d> wrap->pos = <%d>", sh->term.win.ws_col, wrap->pos);
		dprintf(g_fd, "\nlast line = <%d>", is_last_line(wrap->pos, ft_count_string(wrap->head), sh->term.win.ws_col));
	}
	return (0);
}

int				ft_print_list(t_dlist_wrap *wrap, t_sh *sh)
{
	t_chr	*schar;
	t_dlist	*list;

	ft_prompt(sh);
	if (sh->ret == Q_OK)
		list = wrap->head;
	else
		list = wrap->tmp;

	while (list != NULL)
	{
		schar = list->content;
		write(STDOUT_FILENO, &schar->c, 1);
		list = list->next;
	}
	return (0);
}

int			ft_count_wrap(t_dlist_wrap *wrap, t_sh *sh)
{
	t_dlist	*list;
	int		count;

	count = 0;
	if (sh->ret == Q_OK)
		list = wrap->head;
	else
		list = wrap->tmp;
	if (sh->ret != Q_OK && list)
		list = list->next;
	while (list != NULL)
	{
		count++;
		list = list->next;
	}
	return (count);
}


int			ft_count_string(t_dlist *lst)
{
	t_dlist	*list;
	int		count;

	count = 0;
	list = lst;
	while (list != NULL)
	{
		count++;
		list = list->next;
	}
	return (count);
}

