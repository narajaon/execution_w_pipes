/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:58:08 by awyart            #+#    #+#             */
/*   Updated: 2018/03/08 13:58:11 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int				ft_quote(t_dlist_wrap *wrap, t_sh *sh)
{
	char	buf[3];

	if (sh->ret == Q_OK)
		return (sh->ret);
	wrap->pos = wrap->size;
	wrap->tmp = cur_list(wrap);
	ft_terms_toggle_key("cr");
	ft_terms_toggle_key("do");
	ft_prompt(sh);
	while (1)
	{
		ioctl(1, TIOCGWINSZ, &(sh->term.win));
		wrap->col = sh->term.win.ws_col;
		ft_bzero(buf, 3);
		read(STDIN_FILENO, buf, 3);
		if (apply_cap(buf, wrap, sh) == 0)
			break ;
	}
	if ((sh->ret = ft_handle_quote(wrap->head)) != Q_OK)
		sh->ret = ft_quote(wrap, sh);
	if (sh->ret == Q_OK)
		wrap->tmp = NULL;
	return (sh->ret);
}

static void		change_last(t_chr *schar, char *last)
{
	if (schar->c == '\"' && *last == '\"')
		*last = '.';
	else if (schar->c == '\'' && *last == '\'')
		*last = '.';
	else if (schar->c == '\"' && *last == '.')
		*last = '\"';
	else if (schar->c == '\'' && *last == '.')
		*last = '\'';
}

static char		check_quote(t_dlist *list)
{
	t_chr	*schar;
	t_chr	*prev;
	char	last;

	schar = NULL;
	prev = NULL;
	last = '.';
	if (list != NULL)
		prev = list->content;
	while (list != NULL)
	{
		schar = list->content;
		if (prev && (prev->c != '\\' || last == '\''))
			change_last(schar, &last);
		prev = schar;
		list = list->next;
	}
	return (last);
}

int				ft_handle_quote(t_dlist *list)
{
	char	last;
	t_chr	*schar;
	t_chr	*prev_char;

	schar = NULL;
	prev_char = NULL;
	last = check_quote(list);
	while (list != NULL && list->next != NULL)
		list = list->next;
	if (list != NULL)
		schar = list->content;
	if (last == '\'' || last == '\"')
		return ((last == '\'') ? QUOTE : DQUOTE);
	if (schar && schar->c == '|')
	{
		if (list->prev != NULL)
			prev_char = list->prev->content;
		if (prev_char && prev_char->c != '\\')
			return (Q_PIPE);
	}
	if (schar && schar->c == '\\' && (schar->c = '\n'))
		return (SLASH);
	return (Q_OK);
}
