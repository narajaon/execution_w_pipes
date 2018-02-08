/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchpipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 21:54:45 by awyart            #+#    #+#             */
/*   Updated: 2018/01/17 13:39:20 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void rundest(int mypipe[2], t_process *process, t_sh *sh)
{
	int 	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(mypipe[0], STDIN_FILENO);
		close(mypipe[1]);
		execve(process->argv[0], process->argv, sh->env.env);
		dprintf(STDERR_FILENO, "ERREUR\n");
	}
	else if (pid < 0)
	{
		dprintf(STDERR_FILENO, "ERREUR\n");
		exit(0);
	}
}

void runsource(int mypipe[2], t_process *process, t_sh *sh)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(mypipe[1], STDOUT_FILENO);
		close(mypipe[0]);
		execve(process->argv[0], process->argv, sh->env.env);
		ft_dprintf(STDERR_FILENO, "ERREUR\n");
	}
	else if (pid < 0)
	{
		ft_dprintf(STDERR_FILENO, "ERREUR\n");
		exit(0);
	}
}

int handle_pipe(t_sh *sh, t_btree *btree)
{
	t_process *process1 = NULL;
	t_process *process2 = NULL;

	if (btree->right == NULL || btree->left == NULL)
		return (0);
	if (btree->left->process == NULL)
		dprintf(g_fd, "un process a mal été créé");

	process1 = btree->left->process;
	process2 = btree->right->process;
	if (pipe(mypipe) < 0)
		dprintf(g_fd, "erreur pipe\n");
	runsource(mypipe, process1, sh);
	rundest(mypipe, process2, sh);
	close(mypipe[0]);
	close(mypipe[1]);
	while ((pid = wait(&status)) != -1)	/* pick up all the dead children */
		dprintf(g_fd, "process %d exits with %d\n", pid, WEXITSTATUS(status));
	return (1);

}
