/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_non_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 11:50:33 by awyart            #+#    #+#             */
/*   Updated: 2018/01/29 11:38:19 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void 					ft_init_keytab(void)
{
	int i;

	i = -1;
	while (++i < SCHAR_MAX)
		g_handlenonchar[i] = NULL;
	g_handlenonchar[K_UP] = &move_updown;
	g_handlenonchar[K_DOWN] = &move_updown;
	g_handlenonchar[K_RIGHT] = &move_right;
	g_handlenonchar[K_LEFT] = &move_left;
	g_handlenonchar[K_END] = &move_end;
	g_handlenonchar[K_HOME] = &move_begin;
	g_handlenonchar[K_PUP] = &move_up_ctrl;
	g_handlenonchar[K_PDOWN] = &move_down_ctrl;
	g_handlenonchar[K_DEL] = &handle_del_right;
	g_handlenonchar[K_CUT] = &cut_list;
	g_handlenonchar[K_YANK] = &paste_list;
}

int						get_next_char(char *c)
{
	int ret;

	ret = read(STDIN_FILENO, c, 1);
	return (ret);
}

int						handle_esc(t_dlist_wrap *wrap, t_sh *sh)
{
	char				c;
	int					(*ptr)() = NULL;

	if (get_next_char(&c) == -1)
		return (-1);
	if (c == 91)
	{
		if (get_next_char(&c) == -1)
			return (-1);
		ptr = g_handlenonchar[(int)c];
		if (ptr != NULL)
			ptr(wrap, sh, c);
		else
			dprintf(g_fd, "<%i>\n", c);
	}
	return (1);
}

int						handle_cut(t_dlist_wrap *wrap, t_sh *sh, int c)
{
	int			(*handle)();

	handle = g_handlenonchar[c];
	handle(wrap, sh);
	return (1);
}

int						handle_non_char(char c, t_dlist_wrap *wrap, t_sh *sh)
{
	if (c == '\n')
		return (0);
	else if (c == 27)
		return (handle_esc(wrap, sh));
	else if (c == 127)
		return (handle_del(wrap, sh));
	else if (c == 11 || c == 12)
		return (handle_cut(wrap, sh, c));
	return (1);
}
