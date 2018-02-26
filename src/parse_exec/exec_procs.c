#include "header.h"

int				exec_prog(char *input)
{
	int			status;
	char		**split;
	char		**bin_paths;
	char		*path;

	status = 0;
	split = extract_redir(input);
	bin_paths = ft_strsplit(ft_getenv(g_sh->env.env, "PATH"), ':');
	path = check_bin(bin_paths, split[0]);
	if (path == NULL)
	{
		if ((is_binary_file(split[0]) == TRUE) &&
				(is_valid_path(split[0]) == TRUE))
		{
			path = split[0];
		}
		else
		{
			ft_dprintf(STDERR_FILENO, "command not found\n");
			exit(EXIT_FAILURE);
		}
	}
	return (execve(path, split, g_sh->env.env));
}

int				exec_in_child(t_dlist *curr, int *cpfd, int *pfd, int cmd_id)
{
	int			status;

	status = 0;
	if (curr->next != NULL)
		dup2(cpfd[1], STDOUT_FILENO);
	if (curr->prev != NULL)
		dup2(pfd[0], STDIN_FILENO);
	close_fd(pfd);
	close_fd(cpfd);
	if (cmd_id < 0)
		status = exec_prog(curr->content);
	if (curr->next != NULL)
		status = exec_builtin(cmd_id, curr->content);
	return (status);
}

int				exec_in_parent(t_dlist *curr, int *cpfd, int *pfd, int cmd_id)
{
	int			status;

	status = 0;
	close_fd(pfd);
	if (cmd_id >= 0)
	{
		if (cmd_id == B_CD)
			status = exec_builtin(cmd_id, curr->content);
		else if (curr->next == NULL)
			status = exec_builtin(cmd_id, curr->content);
	}
	if (curr->next != NULL)
		status = pipe_processes(curr->next, cpfd);
	close_fd(cpfd);
	return (status);
}

int				pipe_processes(t_dlist *curr, int *pfd)
{
	int			status;
	int			cpfd[2];
	int			cmd_id;

	status = 0;
	pipe(cpfd);
	cmd_id = is_builtin(curr->content);
	g_lvl++;
	if ((fork()) == 0)
	{
		status = exec_in_child(curr, cpfd, pfd, cmd_id);
		exit(status);
	}
	else
	{
		exec_in_parent(curr, cpfd, pfd, cmd_id);
	}
	g_lvl--;
	return (status);
}

void			exec_procs(t_dlist *pipes)
{
	int			status;
	int			pfd[2];
	int 		ret;

	status = 0;
	pipe(pfd);
	ret = pipe_processes(pipes, pfd);
	close_fd(pfd);
	if ((waitpid(ret, &status, 0)) == -1)
		exit(0);
	if ((WIFSIGNALED(status)))
	{
		ft_printf("le process s'est terminé anormalement :\n");
		ft_signal2(WTERMSIG(status));
	}
}
