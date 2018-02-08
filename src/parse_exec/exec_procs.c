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
	return (status = execve(path, split, g_sh->env.env));
}

int			pipe_two_processes(t_dlist *curr, int *pfd)
{
	int			pid;
	int			status;
	//int			pipes[2];

	status = 0;
	//STR(curr->content);
	if (curr->prev != NULL)
		read_prev(&pfd[0], &pfd[1]);
	if ((pid = fork()) == 0)
	{
		if (curr->next != NULL)
			write_next(&pfd[0], &pfd[1]);
		status = exec_prog(curr->content);
	}
	if (curr->prev != NULL)
	{
		STR(curr->content);
		read_prev(&pfd[0], &pfd[1]);
	}
	return (status);
}

void			exec_procs(t_dlist *pipes)
{
	int			pfd[2];
	int			status;

	pipe(pfd);
	while (pipes)
	{
		status = pipe_two_processes(pipes, pfd);
		pipes = pipes->next;
	}
	close(pfd[0]);
	close(pfd[1]);
	while (wait(&status) > 0)
		printf("Killing [%#x]\n", status);
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
