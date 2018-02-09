#include "../../inc/header.h"

void		write_next(pid_t *reading, pid_t *writting)
{
	dup2(*reading, STDOUT_FILENO);
	(void)reading;
	close(*reading);
	(void)writting;
}

void		read_prev(pid_t *reading, pid_t *writting)
{
	dup2(*writting, STDIN_FILENO);
	(void)reading;
	close(*reading);
	(void)writting;
}
