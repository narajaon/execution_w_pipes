/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkjob.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 21:17:19 by awyart            #+#    #+#             */
/*   Updated: 2018/01/14 19:51:00 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// void ft_print_process(t_process **process, int fd[3], char *str)
// {
// 	t_process *proc;

// 	proc = *process;
// 	dprintf(g_fd, "\ntest de %s:", str);
// 	dprintf(g_fd, "\nargv0 <%s>, cmd <%s>, last_tok <%d>, next_tok <%d>, bi <%d>\n",
// 				proc->argv[0], proc->cmd, proc->last_tok, proc->next_tok, proc->bi);
// 	dprintf(g_fd, "stdin = <%d>, stdout <%d>, stderr <%d>\n", fd[F_IN], fd[F_OUT], fd[F_ERR]);
// }