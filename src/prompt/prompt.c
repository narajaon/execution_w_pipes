/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:51:28 by awyart            #+#    #+#             */
/*   Updated: 2018/02/21 09:31:33 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_prompt(t_sh *sh)
{
	if (sh->ret == DQUOTE)
		ft_dprintf(STDERR_FILENO, "dquote> ");
	else if (sh->ret == QUOTE)
		ft_dprintf(STDERR_FILENO, "quote> ");
	else if (sh->ret == SLASH)
		ft_dprintf(STDERR_FILENO, "> ");
	else if (sh->ret == Q_PIPE)
		ft_dprintf(STDERR_FILENO, "pipe> ");
	else if (sh->ret == Q_OK)
	{
		if (sh->dir.dir_name != NULL)
			ft_dprintf(STDOUT_FILENO, "%s > ",sh->dir.dir_name);
		else
			ft_dprintf(STDOUT_FILENO, "InvalidDir > ");
	}
	return (1);
}

int	len_prompt(t_sh *sh)
{
	if (sh->ret == DQUOTE)
		return (8);
	else if (sh->ret == QUOTE)
		return (7);
	else if (sh->ret == SLASH)
		return (2);
	else if (sh->ret == Q_PIPE)
		return (6);
	else if (sh->ret == Q_OK)
	{
		if (sh->dir.dir_name != NULL)
			return (ft_strlen(sh->dir.dir_name) + 3);
		return (13);
	}
	return (0);
}
