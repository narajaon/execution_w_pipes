#include "../../inc/header.h"

void			exec_procs(t_dlist *pipes)
{
	int			status;
	int			pfd[2];
	int 		ret;

	status = 0;
	pipe(pfd);
	ret = pipe_processes(pipes, pfd);
	close_fd(pfd);
	while (waitpid(ret, &status, 0) > 0)
		;
	if ((WIFSIGNALED(status)))
	{
		ft_printf("le process <%d> s'est terminé anormalement :\n", g_cur_pid);
		ft_signal2(WTERMSIG(status));
	}
}

int				iter_thru_procs(t_proc *process)
{
	t_dlist		*semi;
	t_dlist		*pipes;

	pipes = NULL;
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

int				dlist_to_str(char *buff, t_dlist *input)
{
	t_chr		*content;
	int			i;

	i = 0;
	while (input)
	{
		content = input->content;
		buff[i++] = content->c;
		input = input->next;
	}
	buff[i] = '\0';
	return (i);
}

int				exec_cmd(t_dlist *input)
{
	char		*buffer;
	int			buff_size;
	t_proc		process;

	g_cur_pid = 0;
	buff_size = hlst_size(input);
	if (!(buffer = (char *)malloc(sizeof(char) * (buff_size  + 1))))
		return (EXIT_FAILURE);
	dlist_to_str(buffer, input);
	process.semicol = init_proc_list(buffer, ';');
	process.pipes = NULL;
	iter_thru_procs(&process);
	free_hlist(&process.semicol);
	free_str(&buffer);
	return (EXIT_SUCCESS);
}
