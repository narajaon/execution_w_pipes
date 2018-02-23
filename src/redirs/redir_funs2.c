#include "../../inc/header.h"

void			redir_fd(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
}

bool		next_is_fd(char *input, int src)
{
	int		dst;

	dst = 0;
	if (*input != '&')
		return (FALSE);
	input++; /*skip '&'*/
	if (*input == '-')
		close(src);
	else
	{
		if ((dst = ft_atoi(input)) > MAX_FD)
		{
			ft_putstr_fd("invalid file descriptor\n", STDERR_FILENO);
			return (TRUE);
		}
		redir_fd(dst, src);
	}
	return (TRUE);
}

void		heredoc_err_handler(char *input)
{
	(void)input;
}
