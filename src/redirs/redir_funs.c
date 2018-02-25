#include "../../inc/header.h"

const t_red		g_redir[R_NB + 1] =
{
	{"<", R_LEFT, &r_left},
	{">", R_RIGHT, &r_right},
	{"<<", R_DLEFT, &r_dleft},
	{">>", R_DRIGHT, &r_dright},
	{NULL, -1, NULL}
};

int			r_right(char *input)
{
	int			src;
	int			dst;

	src = check_src_fd(input, STDOUT_FILENO);
	while (*input && ft_isdigit(*input) == TRUE)
		input++;
	input++; /*skip character '>'*/
	if (next_is_fd(input, src) == TRUE)
		return (EXIT_SUCCESS);
	while (*input && ft_isspace(*input) == TRUE)
		input++;
	if ((dst = fd_to_file(input, O_WRONLY | O_TRUNC | O_CREAT)) < 0)
		return (EXIT_FAILURE);
	redir_fd(dst, src);
	return (EXIT_SUCCESS);
}

int			r_dright(char *input)
{
	int			src;
	int			dst;

	src = check_src_fd(input, STDOUT_FILENO);
	while (*input && ft_isdigit(*input) == TRUE)
		input++;
	input += 2; /*skip character '>>'*/
	if (next_is_fd(input, src) == TRUE)
		return (EXIT_SUCCESS);
	while (*input && ft_isspace(*input) == TRUE)
		input++;
	if ((dst = fd_to_file(input, O_WRONLY | O_APPEND | O_CREAT)) < 0)
		return (EXIT_FAILURE);
	redir_fd(dst, src);
	return (EXIT_SUCCESS);
}

int			r_left(char *input)
{
	int			src;
	int			dst;

	src = check_src_fd(input, STDIN_FILENO);
	while (*input && ft_isdigit(*input) == TRUE)
		input++;
	input++; /*skip character '<'*/
	if (next_is_fd(input, src) == TRUE)
		return (EXIT_SUCCESS);
	while (*input && ft_isspace(*input) == TRUE)
		input++;
	if ((dst = fd_to_file(input, O_RDONLY | O_CREAT)) < 0)
		return (EXIT_FAILURE);
	redir_fd(dst, src);
	return (EXIT_SUCCESS);
}

int			r_dleft(char *input) /*heredoc*/
{
	int			src;
	int			dst;
	char		*str;

	src = check_src_fd(input, STDIN_FILENO);
	while (*input && ft_isdigit(*input) == TRUE)
		input++;
	input += 2; /*skip character '<<'*/
	while (*input && ft_isspace(*input) == TRUE)
		input++;
	str = handle_heredoc(input, g_sh);
	if ((dst = fd_to_file(HEREFILE, O_RDWR | O_TRUNC)) < 0)
		return (EXIT_FAILURE);
	write(dst, str, ft_strlen(str));
	write(dst, "\n", 1);
	close(dst);
	if ((dst = fd_to_file(HEREFILE, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	redir_fd(dst, src);
//	close(dst);
	return (EXIT_SUCCESS);
}


int			do_redirs(t_dlist *redirs)
{
	int			id;

	//hl_print_next(redirs, &hl_print_str);
	id = redir_id(redirs->content);
	return (g_redir[id].funct(redirs->content));
}
