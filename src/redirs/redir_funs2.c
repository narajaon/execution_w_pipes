/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_funs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:46:58 by awyart            #+#    #+#             */
/*   Updated: 2018/03/20 17:24:52 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		redir_fd(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
}

bool		next_is_fd(char *input, int src)
{
	int		dst;

	dst = 0;
	if (*input != '&')
		return (FALSE);
	input++;
	if (*input == '-')
		close(src);
	else
	{
		if ((dst = ft_atoi(input)) > MAX_FD)
		{
			ft_putstr_fd("invalid file descriptor\n", STDERR_FILENO);
			return (TRUE);
		}
		redir_fd(dst, src);
	}
	return (TRUE);
}

void		init_stdio(int *stdio)
{
	stdio[0] = dup(STDIN_FILENO);
	stdio[1] = dup(STDOUT_FILENO);
	stdio[2] = dup(STDERR_FILENO);
}

void		dup_stdio(int *stdio)
{
	dup2(stdio[0], STDIN_FILENO);
	dup2(stdio[1], STDOUT_FILENO);
	dup2(stdio[2], STDERR_FILENO);
}

void		close_stdio(int *stdio)
{
	close(stdio[0]);
	close(stdio[1]);
	close(stdio[2]);
}
