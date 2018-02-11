#include "../../inc/header.h"

int			exec_prog(char *input)
{
	int		status;
	char	**split;
	char	**bin_paths;
	char	*path;

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
	int			pid1;
	int			cpfd[4];

	status = 0;
	pipe(cpfd);
	pipe(cpfd + 2);
	if ((pid1 = fork()) == 0)
	{
		if (curr->prev == NULL && curr->next != NULL)
		{
			dup2(cpfd[1], STDOUT_FILENO);
			dprintf(g_fd, "\n\nfirst == %s fd = %d\n\n", curr->content, cpfd[1]);
		}
		else if (curr->prev != NULL && curr->next != NULL)
		{
			dup2(pfd[0], STDIN_FILENO);
			dup2(cpfd[1], STDOUT_FILENO);
			dprintf(g_fd, "\n\nmid == %s fd = %d %d\n\n", curr->content, pfd[0], cpfd[1]);
		}
		else if (curr->prev != NULL && curr->next == NULL)
		{
			dup2(pfd[0], STDIN_FILENO);
			dprintf(g_fd, "\n\nlast == %s fd = %d\n\n", curr->content, pfd[0]);
		}
		close_fd(pfd);
		close_fd(cpfd);
		exec_prog(curr->content);
	}
	else
	{
		if (curr->next != NULL)
			pipe_processes(curr->next, cpfd);
		close_fd(pfd);
		close_fd(cpfd);
	}
	return (status);
}

void			exec_procs(t_dlist *pipes)
{
	int			status;
	//int			pid;
	int			pfd[4];

	status = 0;
	pipe(pfd);
	pipe(&pfd[2]);
	status = pipe_processes(pipes, pfd);
	close_fd(pfd);
	while (wait(&status) > 0)
		printf("Kill [%#x]\n", status);
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
