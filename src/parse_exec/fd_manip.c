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

void		close_fd(int *pfd)
{
	close(pfd[0]);
	close(pfd[1]);
	close(pfd[2]);
	close(pfd[3]);
}
