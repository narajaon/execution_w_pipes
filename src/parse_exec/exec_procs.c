#include "../../inc/header.h"

int			exec_prog(char *input)
{
	int		status;
	char	**split;
	char	**bin_paths;
	char	*path;

	dprintf(g_fd, "<<<<< %s >>>>\n", input);
	split = ft_strsplit(input, ' ');
	bin_paths = ft_strsplit(ft_getenv(g_sh->env.env, "PATH"), ':');
	if (!(path = check_bin(bin_paths, split[0])))
	{
		ft_putstr("cmd not found\n");
		exit(EXIT_FAILURE);
	}
	status = execve(path, split, g_sh->env.env);
	return (status);
}

int				pipe_processes(t_dlist *curr, int *pfd)
{
	int			status;
	int			cpfd[2];
	int			pid;

	(void)pfd;
	status = 0;
	if (curr == NULL)
		return (status);
	pipe(cpfd);
	close(cpfd[0]);
	if (pfd != NULL)
	{
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[1]);
		status = exec_prog(curr->content);
	}
	if ((pid = fork()) == 0)
	{
		close(cpfd[1]);
		dup2(cpfd[1], STDOUT_FILENO);
		pipe_processes(curr->next, cpfd);
	}
	return (status);
}

void			exec_procs(t_dlist *pipes)
{
	int			status;
	int			pid;

	if (pipes->next != NULL)
		status = pipe_processes(pipes, NULL);
	else
	{
		if ((pid = fork()) == 0)
			status = exec_prog(pipes->content);
	}
	while (wait(&status) > 0)
		printf("Kill [%d]\n", status);
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
		//free(pipes);
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
	//	hl_print_next(process.semicol, hl_print_str);
	process.pipes = NULL;
	iter_thru_procs(&process);
	return (EXIT_SUCCESS);
}
