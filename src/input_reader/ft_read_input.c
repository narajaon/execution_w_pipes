/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 11:50:33 by awyart            #+#    #+#             */
/*   Updated: 2018/01/29 15:39:06 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_no_printable(char c)
{
	if (c < 32 || c > 125)
		return (1);
	return (0);
}

int		ft_read(t_sh *sh)
{
	t_dlist_wrap		wrap;
	char				c;
	int					ret;

	ioctl(1, TIOCGWINSZ, &(sh->term.win));
	ft_bzero(&wrap, sizeof(t_dlist_wrap));
	while (1)
	{
		read(0, &c, 1);
		if (c == 4)
			break ;
		if (ft_no_printable(c))
		{
			if ((ret = handle_non_char(c, &wrap, sh)) == 0)
				break ;
		}
		else
			handle_char(c, &wrap, sh);
		ft_refresh_line(&wrap, sh);
		ft_printlist(&wrap, sh);
	}
	sh->ret = ft_handle_quote(wrap.head);
	if (sh->ret != Q_OK)
		ft_quote(&wrap, sh);
	sh->list = wrap.head;
	ft_put_wrap_end(&wrap, sh);
	ft_refresh_line(&wrap, sh);
	return (1);
}
