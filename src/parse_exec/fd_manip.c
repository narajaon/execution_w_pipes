#include "../../inc/header.h"

const t_red		g_redir[R_NB + 1] =
{
	{"<", R_LEFT, NULL},
	{">", R_RIGHT, NULL},
	{"<<", R_DLEFT, NULL},
	{">>", R_DRIGHT, NULL},
	{NULL, -1, NULL}
};

void			close_fd(int *pfd)
{
	close(pfd[0]);
	close(pfd[1]);
}

int				get_redir(char *av)
{
	if (*av == '>')
		return ((*(av + 1) == '>') ? R_DRIGHT : R_RIGHT);
	if (*av == '<')
		return ((*(av + 1) == '<') ? R_DLEFT : R_LEFT);
	return (-1);
}

void			redir_fd(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
	close(old_fd);
}

int				fd_to_file(int fd, int o_right, int o_perm, char *file)
{
	int			new_fd;

	new_fd = open(file, o_right, o_perm);
	redir_fd(fd, new_fd);
	return (new_fd);
}
