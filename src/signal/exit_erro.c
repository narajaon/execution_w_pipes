/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_erro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:42:20 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 18:42:23 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			exit_error(char *erro_msg, int exit_id)
{
	if (erro_msg != NULL)
		ft_putstr_fd(erro_msg, STDERR_FILENO);
	exit(exit_id);
	return (-1);
}
