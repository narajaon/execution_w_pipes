#include "header.h"

int	iter_thru_procs(t_proc *process)
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

int	exec_cmd(t_dlist *input)
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
