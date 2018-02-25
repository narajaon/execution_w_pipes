#include "header.h"

void			exit_error(char *erro_msg, int exit_id)
{
	if (erro_msg != NULL)
		ft_putstr_fd(erro_msg, STDERR_FILENO);
	exit(exit_id);
}
