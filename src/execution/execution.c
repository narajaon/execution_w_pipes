/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:05:26 by awyart            #+#    #+#             */
/*   Updated: 2018/01/24 12:23:21 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

		// if (process->file != NULL)
		// {
		// 	while (process->file)
		// 	{
		// 		if (process->file->type == RSREDIR)
		// 		{
		// 			dprintf(g_fd, "RSREDIR detected\n");
		// 			if (!(fd = open(process->file->name[0], O_CREAT | S_IRWXO)))
		// 				dprintf(g_fd, "erreur dans l'ouverture du fichier\n");
		// 			dup2(fd, STDOUT_FILENO);
		// 			close(STDOUT_FILENO);
		// 		}
		// 		else if (process->file->type == RDREDIR)
		// 		{
		// 			dprintf(g_fd, "RRDREDIR detected\n");
		// 			if (!(fd = open(process->file->name[0], O_CREAT | S_IRWXO | O_APPEND)))
		// 				dprintf(g_fd, "erreur dans l'ouverture du fichier\n");
		// 			dup2(fd, STDOUT_FILENO);
		// 			close(STDOUT_FILENO);
		// 		}
		// 		else if (process->file->type == LREDIR)
		// 		{
		// 			dprintf(g_fd, "LREDIR detected\n");
		// 			if (!(fd = open(process->file->name[0], S_IRWXO)))
		// 				dprintf(g_fd, "erreur dans l'ouverture du fichier\n");
		// 			while (read(fd, &buf, 1) == 1)
		// 				write(STDIN_FILENO, &buf, 1);
		// 		}
		// 		else if (process->file->type == HEREDOC)
		// 			dprintf(g_fd, "invoquer heredoc pls\n");
		// 		dprintf(g_fd, " le type vaut <%d>\n", process->file->type);
		// 		process->file = process->file->next;
		// 	}
		// }


void rundest(int mypipe[2], int pipe[2], t_btree *btree, t_sh *sh)
{
	t_process 	*process = NULL;
	int fd;
	char buf;

	process = btree->right->process;
	if (process->bi != B_NONE)
	{
		ft_exec_build_in(sh, process);
		dprintf(g_fd, "<%d>BI exec\n", process->bi);
		return ;
	}
	process->pid = fork();
	if (process->file != NULL)
	{
		while (process->file)
		{
			if (process->file->type == RSREDIR)
			{
				dprintf(g_fd, "RSREDIR detected\n");
				if (!(fd = open(process->file->name[0], O_CREAT | S_IRWXO)))
					dprintf(g_fd, "erreur dans l'ouverture du fichier\n");
				dup2(fd, STDOUT_FILENO);
				close(STDOUT_FILENO);
			}
			else if (process->file->type == RDREDIR)
			{
				dprintf(g_fd, "RRDREDIR detected\n");
				if (!(fd = open(process->file->name[0], O_CREAT | S_IRWXO | O_APPEND)))
					dprintf(g_fd, "erreur dans l'ouverture du fichier\n");
				dup2(fd, STDOUT_FILENO);
				close(STDOUT_FILENO);
			}
			else if (process->file->type == LREDIR)
			{
				dprintf(g_fd, "LREDIR detected\n");
				if (!(fd = open(process->file->name[0], S_IRWXO)))
					dprintf(g_fd, "erreur dans l'ouverture du fichier\n");
				while (read(fd, &buf, 1) == 1)
					write(STDIN_FILENO, &buf, 1);
			}
			else if (process->file->type == HEREDOC)
				dprintf(g_fd, "invoquer heredoc pls\n");
			dprintf(g_fd, " le type vaut <%d>\n", process->file->type);
			process->file = process->file->next;
		}
	}
	if (process->pid == 0)
	{
		if (btree->left->type == PIPE)
		{
			dup2(mypipe[0], STDIN_FILENO);
			close(mypipe[1]);
		}
		if (pipe && btree->type == PIPE)
		{
			dup2(pipe[1], STDOUT_FILENO);
			close(pipe[0]);
		}
		process->cmd = ft_create_cmd(sh, process);
		execve(process->cmd, process->argv, sh->env.env);
		ft_dprintf(STDERR_FILENO, "ERREUR\n");
		exit(0);
	}
	else if (process->pid < 0)
	{
		dprintf(STDERR_FILENO, "ERREUR\n");
		exit(0);
	}
}

void runsource(int mypipe[2], t_btree *btree, t_sh *sh)
{
	t_process *process = NULL;

	process = btree->left->process;
	if (process->bi != B_NONE)
	{
		ft_exec_build_in(sh, process);
		dprintf(g_fd, "<%d>BI exec\n", process->bi);
		return ;
	}
	process->pid = fork();
	//gerer les redir
	if (process->pid == 0)
	{
		if (btree->type == PIPE)
		{
			dup2(mypipe[1], STDOUT_FILENO);
			close(mypipe[0]);
		}
		process->cmd = ft_create_cmd(sh, process);
		execve(process->cmd, process->argv, sh->env.env);
		ft_dprintf(STDERR_FILENO, "ERREUR\n");
		exit(0);
	}
	else if (process->pid < 0)
	{
		ft_dprintf(STDERR_FILENO, "ERREUR\n");
		exit(0);
	}
}

int exec_source(t_sh *sh, t_btree *btree)
{
	t_process *process;

	process = btree->process;
	dprintf(g_fd, "process ok...\n");
	if (process->bi != B_NONE)
	{
		ft_exec_build_in(sh, process);
		dprintf(g_fd, "<%d>BI exec\n", process->bi);
		return (1);
	}
	process->pid = fork();
	//gerer les redir
	dprintf(g_fd, "fork ok...\n");
	if (process->pid == 0)
	{
		process->cmd = ft_create_cmd(sh, process);
		execve(process->cmd, process->argv, sh->env.env);
		ft_dprintf(STDERR_FILENO, "ERREUR\n");
		exit(0);
	}
	else if (process->pid < 0)
	{
		ft_dprintf(STDERR_FILENO, "ERREUR\n");
		exit(0);
	}
	return (1);
}

int exec_tree(t_sh *sh, t_btree *btree, int ypipe[2])
{
	int mypipe[2];
	int pid;
	int status;

	if (btree && btree->left)
	{
		if (btree->type == PIPE && pipe(mypipe) < 0)
			dprintf(g_fd, "erreur pipe\n");
		if (btree->left->process != NULL)
		{
			dprintf(g_fd, "on a identifié que btree->left->process n'etait pas null\n");
			runsource(mypipe, btree, sh);
		}
		else
		{
			dprintf(g_fd, "checkin2\n");
			exec_tree(sh, btree->left, mypipe);
		}
		rundest(mypipe, ypipe, btree, sh);
		close(mypipe[0]);
		close(mypipe[1]);
		while ((pid = wait(&status)) != -1)	/* pick up all the dead children */
			dprintf(g_fd, "process %d exits with %d\n", pid, WEXITSTATUS(status));
	}
	return (1);
}

void ft_execution(t_sh *sh)
{
	t_btree *btree = NULL;
	int i;
	int mypipe[2];
	int pid;
	int status;

	i = 0;
	while (sh->btree[i] != NULL)
	{
		btree = sh->btree[i];
		if (btree)
			ft_print_tree(btree);
		if (btree && btree->left)
		{
			if (btree->type == PIPE && pipe(mypipe) < 0)
					dprintf(g_fd, "erreur pipe\n");
			if (btree->left->process != NULL)
				runsource(mypipe, btree, sh);
			else
				exec_tree(sh, btree->left, mypipe);
			rundest(mypipe, NULL, btree, sh);
			close(mypipe[0]);
			close(mypipe[1]);
		}
		else
		{
			if (btree)
				exec_source(sh, btree);
		}
		while ((pid = wait(&status)) != -1)	/* pick up all the dead children */
			dprintf(g_fd, "process %d exits with %d\n", pid, WEXITSTATUS(status));
		i++;
	}
}
