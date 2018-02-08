/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:46:42 by awyart            #+#    #+#             */
/*   Updated: 2018/02/02 14:54:21 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int 		is_last_line(int pos, int end, int col)
{
	int c1;
	int c2;

	c1 = 0;
	c2 = 0;
	while (pos >= col)
	{
		pos -= col;
		c1++;
	}
	while (end >= col)
	{
		end -= col;
		c2++;
	}
	if (c1 == c2)
		return (1);
	return (0);
}

int 	ft_reset_cursor(t_dlist_wrap *wrap, t_sh *sh, int pos)
{
	int offset;
	int size;

	size = ft_count_wrap(wrap, sh) + len_prompt(sh);
	offset = size - pos + 1;
	while (--offset)
	{
		if (offset <= 0)
			break;
		ft_terms_toggle_key("le");
	}
	if ((pos + 1) % sh->term.win.ws_col == 0 && wrap->cursor == NULL)
	{
		ft_terms_toggle_key("cr");
		ft_terms_toggle_key("do");
		ft_terms_toggle_key("al");
	}
	return (size - wrap->pos);
}

int 	ft_refresh_line(t_dlist_wrap *wrap, t_sh *sh)
{
	int i;
	int col;
	int pos;

	//dprintf(g_fd, "\33[H\33[2JLIST \n");
	if (sh->ret == Q_OK)
		pos = wrap->pos + len_prompt(sh);
	else
		pos = ft_count_string(wrap->tmp) + len_prompt(sh);
	col = sh->term.win.ws_col;
	if (col < 10)
	{
		dprintf(g_fd, "fenetre trop petite\n");
		exit(0);
	}
	if (wrap && wrap->last_mov == DEL)
		i = (pos + 2)/ (col) + 1;
	else if (wrap && wrap->last_mov == LEFT)
		i = (pos + 2)/ (col) + 1;
	else
		i = (pos) / (col) + 1;
	//dprintf(g_fd, "i <%d> col <%d> pos <%d>last <%d>", i, col, pos, wrap->last_mov);
	while (--i)
	{
		if (i <= 0)
			break ;
		ft_terms_toggle_key("cr");
		ft_terms_toggle_key("cd");
		ft_terms_toggle_key("al");
		ft_terms_toggle_key("up");
	}
	ft_terms_toggle_key("cr");
	ft_terms_toggle_key("cd");
	ft_terms_toggle_key("al");
	ft_print_list(wrap, sh);
	ft_reset_cursor(wrap, sh, pos);
	return (1);
}