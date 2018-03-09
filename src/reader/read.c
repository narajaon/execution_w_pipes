/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/09 16:03:34 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			ft_quit(void)
{
	tcsetattr(0, TCSANOW, &(g_sh->term.prev_term));
	flush_sh(g_sh);
	exit(0);
}

int			get_func(char buf[8])
{
	int i;
	int k;

	i = -1;
	k = 2;
	if (is_printable(buf))
		return (-1);
	while (++i < CAP_SIZE)
	{
		if (ft_strncmp(buf, g_handleinput[i].cap, 8) == 0)
			return (i);
	}
	return (-2);
}

int			apply_cap(char buf[8], t_dlist_wrap *wrap, t_sh *sh)
{
	int ret;
	int (*ptr)();

	ret = 0;
	ptr = NULL;
	if (buf[0] == 10)
	{
		refresh_line(wrap, sh);
		return (0);
	}
	ret = get_func(buf);
	if (ret >= 0)
	{
		ptr = g_handleinput[ret].f;
		ret = ptr(wrap, buf, sh);
	}
	else if (ret == -1)
		handle_char(buf[0], wrap);
	refresh_line(wrap, sh);
	reset_cursor(wrap, sh);
	sh->test = 0;
	return (1);
}

int			ft_read(t_sh *sh)
{
	char			buf[8];
	t_dlist_wrap	*wrap;

	if (!(wrap = (t_dlist_wrap *)ft_memalloc(sizeof(t_dlist_wrap))))
		return (0);
	sh->wrap = wrap;
	wrap->yanked = sh->yanked;
	while (1)
	{
		ioctl(1, TIOCGWINSZ, &(sh->term.win));
		wrap->col = sh->term.win.ws_col;
		ft_bzero(buf, 8);
		read(STDIN_FILENO, buf, 8);
		//dprintf(g_fd, "<%d><%d><%d><%d><%d><%d><%d><%d>\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
		if (apply_cap(buf, wrap, sh) == 0)
			break ;
	}
	sh->ret = ft_handle_quote(wrap->head);
	if (sh->ret != Q_OK)
		ft_quote(wrap, sh);
	sh->list = ft_dlist_dup(wrap->head, sizeof(t_chr));
	sh->yanked = ft_dlist_dup(wrap->yanked, sizeof(t_chr));
	free_hlist(&wrap->yanked);
	free_hlist(&wrap->head);
	wrap->tmp = NULL;
	return (1);
}
