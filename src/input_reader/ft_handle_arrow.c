/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_arrow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:52:28 by awyart            #+#    #+#             */
/*   Updated: 2018/01/22 10:42:01 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void 		move_cursor_left(t_dlist_wrap *wrap, t_sh *sh)
{
	int pos;
	int col;

	pos = wrap->pos + len_prompt(sh);
	col = sh->term.win.ws_col;
	if (pos % col == 1)
	{
		ft_terms_toggle_key("up");
		while (col)
		{
			ft_terms_toggle_key("nd");
			col--;
		}
	}
	else
		ft_terms_toggle_key("le");
}


int 	move_dlist_left(t_dlist_wrap *wrap)
{
	if (wrap->head == NULL || wrap->last == NULL)
		return (0);
	if (wrap->tmp && wrap->cursor == wrap->tmp->next)
		return (0);
	wrap->cursor = wrap->last;
	wrap->last = wrap->last->prev;
	return (1);
}


int			move_left(t_dlist_wrap *wrap, t_sh *sh)
{

	if (move_dlist_left(wrap) == 1)
	{
		wrap->pos--;
		wrap->last_mov = LEFT;
		return (1);
	}
	sh->offset = 0;
	return (0);
}

// void 		move_cursor_right(t_dlist_wrap *wrap, t_sh *sh)
// {
// 	int pos;
// 	int col;

// 	pos = wrap->pos + len_prompt(sh);
// 	col = sh->term.win.ws_col;
// 	if (pos % col == 0)
// 	{
// 		ft_terms_toggle_key("cr");
// 		ft_terms_toggle_key("do");
// 	}
// 	else
// 		ft_terms_toggle_key("nd");
// }


int 	move_dlist_right(t_dlist_wrap *wrap)
{
	if (wrap->cursor == NULL || wrap->cursor->content == NULL)
		return (0);
	wrap->last = wrap->cursor;
	wrap->cursor = wrap->cursor->next;
	return (1);
}

int			move_right(t_dlist_wrap *wrap, t_sh *sh)
{
	if (move_dlist_right(wrap) == 1)
	{
		wrap->pos++;
		wrap->last_mov = RIGHT;
		return (1);
	}
	sh->offset = 0;
	return (0);
}

static void	printlist(t_dlist *list)
{
	t_chr  *schar;

	while (list != NULL)
	{
		schar = list->content;
		if (schar  == NULL)
			exit(3);
		dprintf(1, "%c", schar->c);
		list = list->next;
	}
}

int			move_up(t_dlist_wrap *wrap, t_sh *sh, int mode)
{
	t_dlist		*list;
	t_dlist     *begin;
	int 	i;

	if (sh->ret == Q_OK)
		begin = wrap->head;
	else
		begin = wrap->tmp;
	//history_handler(IR_UP, wrap->head, sh->hist);
	list = completion_res(IR_UP, begin, sh->hist);
	if (mode == 0)
		i = (wrap->pos + len_prompt(sh)) / sh->term.win.ws_col + 1;
	else
		i = (ft_count_string(list) + len_prompt(sh)) / sh->term.win.ws_col + 1;
	while (--i)
	{
		ft_terms_toggle_key("cr");
		ft_terms_toggle_key("dl");
		ft_terms_toggle_key("al");
		ft_terms_toggle_key("up");
	}	
	ft_terms_toggle_key("cr");
	ft_terms_toggle_key("dl");
	ft_terms_toggle_key("al");
	ft_prompt(sh);
	printlist(list);
	return (1);
}

int			move_down(t_dlist_wrap *wrap, t_sh *sh, int mode)
{
	t_dlist		*list;
	t_dlist     *begin;
	int 		i;

	if (sh->ret == Q_OK)
		begin = wrap->head;
	else
		begin = wrap->tmp;
	list = completion_res(IR_DOWN, wrap->head, sh->hist);
	if (mode == 0)
		i = (wrap->pos + len_prompt(sh)) / sh->term.win.ws_col + 1;
	else
		i = (ft_count_string(list) + len_prompt(sh)) / sh->term.win.ws_col + 1;
	while (--i)
	{
		ft_terms_toggle_key("cr");
		ft_terms_toggle_key("dl");
		ft_terms_toggle_key("al");
		ft_terms_toggle_key("up");
		}	
	ft_terms_toggle_key("cr");
	ft_terms_toggle_key("dl");
	ft_terms_toggle_key("al");
	ft_prompt(sh);
	if (list == NULL)
		printlist(wrap->head);
	else
		printlist(list);
	return (1);
}

int			ft_modif(t_sh *sh, t_dlist_wrap *wrap)
{
	t_dlist		*last;

	last = wrap->head;
	wrap->head = sh->hist->cur_branch;
	wrap->cursor = sh->hist->cur_branch;
	wrap->last = NULL;
	ft_put_wrap_end(wrap, sh);
	wrap->pos = ft_count_string(wrap->head);
	wrap->tmp = NULL;
	ft_refresh_line(wrap, sh);
	return (1);
}

int			get_pressed_key(void)
{
	char c;

	if (get_next_char(&c) == -1 || c != 27)
	{
		//clear_read();
		if (!c)
			return (-1);
		return (0);
	}
	if (get_next_char(&c) == -1 || c != 91)
	{
		//clear_read();
		return (0);
	}
	if (get_next_char(&c) == -1)
	{
		//clear_read();
		return (0);
	}
	return ((int)c);
}

int			move_updown(t_dlist_wrap *wrap, t_sh *sh, char c)
{
	int		key;

	key = (int)c;
	if (key == K_UP)
		move_up(wrap, sh, 0);
	else if (key == K_DOWN)
		move_down(wrap, sh, 0);
	while (1)
	{
		key = get_pressed_key();
		if (key != K_UP && key != K_DOWN)
		{
			//apply key
			break ;
		}
		else if (key == -1)
			continue ;
		if (key == K_UP)
			move_up(wrap, sh, 1);
		else if (key == K_DOWN)
			move_down(wrap, sh, 1);
	}
	ft_modif(sh, wrap);
	sh->hist->cur_branch = NULL;
	completion_res(2, NULL, NULL);
	wrap->last_mov = HIST;
	return (0);
}
