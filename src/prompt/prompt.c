/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:51:28 by awyart            #+#    #+#             */
/*   Updated: 2018/02/21 14:57:06 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_prompt(t_sh *sh)
{
	if (sh->ret == DQUOTE)
		ft_dprintf(STDERR_FILENO, "%sdquote%s > ", KYEL, KNRM);
	else if (sh->ret == QUOTE)
		ft_dprintf(STDERR_FILENO, "%squote%s > ", KYEL, KNRM);
	else if (sh->ret == SLASH)
		ft_dprintf(STDERR_FILENO, " > ");
	else if (sh->ret == Q_PIPE)
		ft_dprintf(STDERR_FILENO, "%spipe%s > ", KYEL, KNRM);
	else if (sh->ret == Q_HEREDOC)
		ft_dprintf(STDERR_FILENO, "%sheredoc %s> ", KBLU, KNRM);
	else if (sh->ret == Q_OK)
	{
		if (sh->dir.dir_name != NULL)
			ft_dprintf(STDERR_FILENO, "%s%s%s > ", KCYN, sh->dir.dir_name, KNRM);
		else
			ft_dprintf(STDERR_FILENO, "%sInvalidDir%s > ", KRED, KNRM);
	}
	return (1);
}

int	len_prompt(t_sh *sh)
{
	if (sh->ret == DQUOTE)
		return (9);
	else if (sh->ret == QUOTE)
		return (8);
	else if (sh->ret == SLASH)
		return (2);
	else if (sh->ret == Q_PIPE)
		return (7);
	else if (sh->ret == Q_HEREDOC)
		return (10);
	else if (sh->ret == Q_OK)
	{
		if (sh->dir.dir_name != NULL)
			return (ft_strlen(sh->dir.dir_name) + 3);
		return (13);
	}
	return (0);
}
