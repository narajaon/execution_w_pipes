/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getterm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 03:40:39 by awyart            #+#    #+#             */
/*   Updated: 2018/02/02 15:24:34 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			ft_init_term(void)
{
	int		success;
	char	*term_type;

	if ((term_type = ft_getenv(environ, "TERM")) == NULL)
	{
		ft_dprintf(STDERR_FILENO,
			"Specify a terminal type with 'setenv TERM <yourtype>\n");
		exit(0);
	}
	if ((success = tgetent(0, term_type)) < 0)
	{
		ft_dprintf(STDERR_FILENO,
			"Couldn't access the termcap data base\n");
		exit(0);
	}
	if (success == 0)
	{
		ft_dprintf(STDERR_FILENO,
			"Terminal type <%S> is not defined\n", term_type);
		exit(0);
	}
	return (success);
}
