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

	status = 0;
	if (curr == NULL)
		return (status);
	if (curr->next != NULL)
	{
		if ((pid1 = fork()) == 0)
		{
			dprintf(g_fd, "\n\ncmd1 name = <%s>\n\n", curr->content);
			dup2(pfd[1], STDOUT_FILENO);
			close(pfd[0]);
			close(pfd[1]);
			status = exec_prog(curr->content);
		}
		else
		{
			dprintf(g_fd, "\n\ncmd2 name = <%s>\n\n", curr->next->content);
			dup2(pfd[0], STDIN_FILENO);
			close(pfd[0]);
			close(pfd[1]);
			status = exec_prog(curr->next->content);
		}
	}
	else
		status = exec_prog(curr->content);
	return (status);
}

void			exec_procs(t_dlist *pipes)
{
	int			status;
	int			pid;
	int			pfd[2];

	status = 0;
	pipe(pfd);
	if ((pid = fork()) == 0)
		status = pipe_processes(pipes, pfd);
	close(pfd[0]);
	close(pfd[1]);
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
