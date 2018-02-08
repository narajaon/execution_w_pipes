#include "../../inc/header.h"

void		write_next(pid_t *input, pid_t *output)
{
	dup2(*output, STDOUT_FILENO);
	(void)input;
	close(*output);
}

void		read_prev(pid_t *input, pid_t *output)
{
	dup2(*input, STDIN_FILENO);
	(void)output;
	close(*input);
}
