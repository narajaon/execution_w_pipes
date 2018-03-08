/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_erro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:42:20 by awyart            #+#    #+#             */
/*   Updated: 2018/03/08 14:10:08 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			exit_error(char *erro_msg, int exit_id, char *cmd_name)
{
	if (cmd_name != NULL)
		ft_dprintf(STDERR_FILENO, "%s: ", cmd_name);
	if (erro_msg != NULL)
		ft_putstr_fd(erro_msg, STDERR_FILENO);
	exit(exit_id);
	return (EXIT_FAILURE);
}
