/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 14:42:43 by awyart            #+#    #+#             */
/*   Updated: 2018/01/11 14:55:48 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int 	ft_put_wrap_end(t_dlist_wrap *wrap, t_sh *sh)
{
	int count;

	count = 0;
	while (move_dlist_right(wrap) == 1)
		count++;
	if (sh->ret != Q_OK)
		wrap->tmp = wrap->last;
	return (count);
}


int		ft_quote(t_dlist_wrap *wrap, t_sh *sh)
{
	char c;

	if (sh->ret == Q_OK)
		return (sh->ret);
	ft_put_wrap_end(wrap, sh);
	ft_refresh_line(wrap, sh);
	ft_terms_toggle_key("cr");
	ft_terms_toggle_key("do");
	ft_prompt(sh);
	while (1)
	{
		read(0, &c, 1);
		if (c == 4)
			break ;
		if (ft_no_printable(c))
		{
			if ((handle_non_char(c, wrap, sh)) == 0)
				break ;
		}
		else
			handle_char(c, wrap, sh);
		ft_refresh_line(wrap, sh);
		ft_printlist(wrap, sh);
	}
	if ((sh->ret = ft_handle_quote(wrap->head)) != Q_OK)
		sh->ret = ft_quote(wrap, sh);
	return (sh->ret);
}

int		ft_handle_quote(t_dlist *list)
{
	char	c;
	t_chr 	*prev = NULL;
	char	last;
	t_chr	*schar;

	last = '.';
	while (list != NULL)
	{
		schar = list->content;
		c = schar->c;
		if (prev && prev->c != '\\')
		{
			if (c == '\"' && last == '\"')
				last = '.';
			else if (c == '\'' && last == '\'')
				last = '.';
			else if (c == '\"' && last == '.')
				last = '\"';
			else if (c == '\'' && last == '.')
				last = '\'';
		}
		prev = schar;
		list = list->next;
	}
	if (last == '\'')
		return (QUOTE);
	if (last == '\"')
		return (DQUOTE);
	if (c == '|')
	{
		schar->c = '\n';
		return (Q_PIPE);
	}
	if (c == '\\')
	{
		schar->c = '\n';
		return (SLASH);
	}
	return (Q_OK);
}
