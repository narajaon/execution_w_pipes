/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchjob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 21:36:53 by awyart            #+#    #+#             */
/*   Updated: 2018/01/22 15:05:55 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// int needtoopenfile(t_process *process, int mypipe[2])
// {
// 	char buf[1024];
// 	int fd0;
// 	int fd;
// 	int ret;

// 	process->pid = fork();
// 	if (process->pid > 0)
// 	{
// 		if ((waitpid(process->ret, &(process->status), 0)) == -1)
// 			exit(0);
// 		if ((WIFSIGNALED(process->status)))
// 		{
// 			ft_dprintf(STDERR_FILENO, "le process s'est terminé anormalement :\n");
// 			ft_signal(WTERMSIG(process->status));
// 		}
// 	}
// 	if (process->pid == 0)
// 	{
// 		fd = dup(mypipe[0]);
// 		if (!(fd0 = open(process->argv[0], O_WRONLY | O_CREAT)))
// 		{
// 			dprintf(g_fd, "erreur dans l' ouverture de <%s>", process->argv[0]);
// 			return (-1);
// 		}
// 		fchmod(fd0, 000777);
// 		dprintf(g_fd, "0<%s>\n", process->argv[0]);
// 		while ((ret = read(fd, &buf , 1024)) > 0)
// 		{
// 			dprintf(g_fd, "\n----YOLO <%s>----\n", buf);
// 			write(fd0, buf, ret);
// 		}
// 		dprintf(g_fd, "fin de boucle\n");
// 		close(fd0);
// 	}

// 	return (0);
// }

// int needpipe(t_process *process)
// {
// 	int a;

// 	a = process->next_tok;
// 	if (a == RSREDIR || a == PIPE || a == RDREDIR || a == LREDIR)
// 		return (1);
// 	return (0);
// }

// /*static int needpipe_v2(t_process *process)
// {
// 	int a;

// 	a = process->last_tok;
// 	if (a == RSREDIR || a == PIPE || a == RDREDIR || a == LREDIR)
// 		return (1);
// 	return (0);
// }*/

// void ft_launch_job(t_sh *sh)
// {
// 	t_process	*process;
// 	int 		mypipe[2];
// 	int			fd[3];

// 	process = sh->process;
// 	fd[F_IN] = STDIN_FILENO;
// 	fd[F_OUT] = STDOUT_FILENO;
// 	fd[F_ERR] = STDERR_FILENO;
// 	dprintf(g_fd, "\nLa liste des process a exec sont : \n");
// 	ft_print_parsoutput(&process);
// 	ft_detect_build_in(&process);
// 	while (process != NULL)
// 	{
// 		ft_print_process(&process, fd, "debut");
// 		if (process->last_tok  == RSREDIR || process->last_tok == PIPE)
// 		{
// 			if (process->last_tok == PIPE)
// 				needtoopenfile(process, mypipe);
// 			process = process->next;
// 			continue ;
// 		}
// 		if (needpipe(process))
// 		{
// 			if (pipe(mypipe) < 0)
// 			{
// 				dprintf(g_fd, "nous avons besoin d'un pipe pour gerer la sortie\n");
// 				ft_dprintf(STDERR_FILENO, "erreur de pipe1\n");
// 			}
// 			fd[F_OUT] = mypipe[1];
// 		}
// 		if (process->bi != B_NONE)
// 		{
// 			dprintf(g_fd, "\nwe entered the buildin Zone, may segFAULT\n");
// 			ft_exec_build_in(sh, process, process->bi);
// 			process = process->next;
// 			continue ;
// 		}
// 		process->cmd = ft_create_cmd(sh, process);
// 		dprintf(g_fd, "\n la commande est <%s>\n", process->cmd);
// 		process->pid = fork();
// 		if (fd[F_OUT] != STDOUT_FILENO)
// 		{
// 			dup2(mypipe[1], STDOUT_FILENO);
// 			//close(mypipe[0]);
// 		}
// 		if (process->pid > 0)
// 		{
// 			if ((waitpid(process->ret, &(process->status), 0)) == -1)
// 				exit(0);
// 			if ((WIFSIGNALED(process->status)))
// 			{
// 				ft_dprintf(STDERR_FILENO, "le process s'est terminé anormalement :\n");
// 				ft_signal(WTERMSIG(process->status));
// 			}
// 		}
// 		if (process->pid == 0)
// 		{
// 			process->ret = execve(process->cmd, process->argv, sh->env.env);
// 			ft_dprintf(STDERR_FILENO, "exec failed\n");
// 			exit(process->ret);
// 		}
// 		ft_print_process(&process, fd, "fin");
// 		if (needpipe(process))
// 		{
// 			dprintf(g_fd, "nous devons utiliser le pipe pour l'entree\n");
// 			handle_pipe(process, mypipe, fd);
// 		}
// 		process = process->next;
// 	}
// 	close(mypipe[1]);
// 	close(mypipe[0]);
// 	//free process
// }
