/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_funs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:46:58 by awyart            #+#    #+#             */
/*   Updated: 2018/03/20 18:31:37 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	input++;
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
	input += 2;
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
	input++;
	if (next_is_fd(input, src) == TRUE)
		return (EXIT_SUCCESS);
	while (*input && ft_isspace(*input) == TRUE)
		input++;
	if ((dst = fd_to_file(input, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	redir_fd(dst, src);
	return (EXIT_SUCCESS);
}

int			r_dleft(char *input)
{
	int			src;
	int			dst;
	char		*str;
	int			output;

	src = check_src_fd(input, STDIN_FILENO);
	close(STDIN_FILENO);
	while (*input && ft_isdigit(*input) == TRUE)
		input++;
	input += 2;
	while (*input && ft_isspace(*input) == TRUE)
		input++;
	output = dup(STDOUT_FILENO);
	dup2(g_sh->stdio[STDOUT_FILENO], STDOUT_FILENO);
	str = handle_heredoc(input, g_sh);
	dup2(output, STDOUT_FILENO);
	close(output);
	if ((dst = fd_to_file(HEREFILE, O_WRONLY | O_TRUNC | O_CREAT)) < 0)
		return (EXIT_FAILURE);
	ft_putendl_fd(&str[1], dst);
	close(dst);
	if ((dst = fd_to_file(HEREFILE, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	redir_fd(dst, src);
	return (EXIT_SUCCESS);
}

int			do_redirs(t_dlist *redirs)
{
	int			id;

	id = redir_id(redirs->content);
	return (g_redir[id].funct(redirs->content));
}
