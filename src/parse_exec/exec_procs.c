#include "../../inc/header.h"

int			exec_prog(char *input)
{
	int			status;
	char		**split;
	char		**bin_paths;
	char		*path;

	status = 0;
	split = ft_strsplit(input, ' ');
	//pas opti, devrait se faire a l'initialisation
	bin_paths = ft_strsplit(ft_getenv(g_sh->env.env, "PATH"), ':');
	//if ((status = is_builtin(split)) >= 0)
	//	return (status);
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
			ft_putstr_fd("cmd not found\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
	return (status = execve(path, split, g_sh->env.env));
}

int				pipe_processes(t_dlist *curr, int *pfd)
{
	int			status;
	int			cpfd[2];
	int			pid;

	status = 0;
	pipe(cpfd);
	if ((pid = fork()) == 0)
	{
		if (curr->next != NULL)
			dup2(cpfd[1], STDOUT_FILENO);
		if (curr->prev != NULL)
			dup2(pfd[0], STDIN_FILENO);
		close_fd(pfd);
		close_fd(cpfd);
		status = exec_prog(curr->content);
	}
	else
	{
		close_fd(pfd);
		if (curr->next != NULL)
			pipe_processes(curr->next, cpfd);
		close_fd(cpfd);
	}
	return (status);
}

void			exec_procs(t_dlist *pipes)
{
	int			status;
	int			pfd[2];

	status = 0;
	pipe(pfd);
	status = pipe_processes(pipes, pfd);
	close_fd(pfd);
	while (wait(&status) > 0)
		;
}

int				iter_thru_procs(t_proc *process)
{
	t_dlist		*semi;
	t_dlist		*pipes;

	semi = process->semicol;
	while (semi != NULL)
	{
		pipes = init_proc_list(semi->content, '|');
		exec_procs(pipes);
		free_hlist(&pipes);
		semi = semi->next;
	}
	return (EXIT_SUCCESS);
}

int				exec_cmd(t_dlist *input)
{
	char		*buffer;
	int			buff_size;
	t_proc		process;

	buff_size = hlst_size(input);
	if (!(buffer = (char *)malloc(sizeof(char) * (buff_size  + 1))))
		return (EXIT_FAILURE);
	input_to_buff(buffer, input);
	process.semicol = init_proc_list(buffer, ';');
	process.pipes = NULL;
	iter_thru_procs(&process);
	free_hlist(&process.semicol);
	free_str(&buffer);
	return (EXIT_SUCCESS);
}
