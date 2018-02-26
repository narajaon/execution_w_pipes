#include "../../inc/header.h"

const t_red		g_redir[R_NB + 1] =
{
	{"<", R_LEFT, &r_left},
	{">", R_RIGHT, &r_right},
	{"<<", R_DLEFT, &r_dleft},
	{">>", R_DRIGHT, &r_dright},
	{NULL, -1, NULL}
};

void			r_right(char *input)
{
	int			src;
	int			dst;

	src = check_src_fd(input, STDOUT_FILENO);
	while (*input && ft_isdigit(*input) == TRUE)
		input++;
	input++;
	if (next_is_fd(input, src) == TRUE)
		return ;
	while (*input && ft_isspace(*input) == TRUE)
		input++;
	dst = fd_to_file(input, O_RDWR | O_TRUNC | O_CREAT);
	redir_fd(dst, src);
}

void			r_dright(char *input)
{
	int			src;
	int			dst;

	src = check_src_fd(input, STDOUT_FILENO);
	while (*input && ft_isdigit(*input) == TRUE)
		input++;
	input += 2;
	if (next_is_fd(input, src) == TRUE)
		return ;
	while (*input && ft_isspace(*input) == TRUE)
		input++;
	dst = fd_to_file(input, O_RDWR | O_APPEND | O_CREAT);
	redir_fd(dst, src);
}

void			r_left(char *input)
{
	int			src;
	int			dst;

	src = check_src_fd(input, STDIN_FILENO);
	while (*input && ft_isdigit(*input) == TRUE)
		input++;
	input++;
	if (next_is_fd(input, src) == TRUE)
		return ;
	while (*input && ft_isspace(*input) == TRUE)
		input++;
	dst = fd_to_file(input, O_RDWR | O_CREAT);
	redir_fd(dst, src);
}

void			r_dleft(char *input)
{
	char *str;

	while (*input && ft_isdigit(*input) == TRUE)
		input++;
	input += 2;
	while (*input == ' ')
		input++;
	str = handle_heredoc(input, g_sh);
}


void			do_redirs(t_dlist *redirs)
{
	int			id;

	id = redir_id(redirs->content);
	g_redir[id].funct(redirs->content);
}
