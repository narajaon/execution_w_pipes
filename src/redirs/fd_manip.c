/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:46:58 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:41:27 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void			close_fd(int *pfd)
{
	close(pfd[0]);
	close(pfd[1]);
}

int				get_redir(char *str)
{
	if (*str == '>')
		return ((*(str + 1) == '>') ? R_DRIGHT : R_RIGHT);
	if (*str == '<')
		return ((*(str + 1) == '<') ? R_DLEFT : R_LEFT);
	return (-1);
}

int				redir_id(char *str)
{
	while (*str && ft_isdigit(*str) == TRUE)
		str++;
	return (get_redir(str));
}

int				fd_to_file(char *file, int perm)
{
	int			new_fd;
	char		**formated;
	char		**tmp;

	tmp = ft_tab_dup((char *[2]){file, NULL});
	formated = fmt_input_quote(tmp);
	if ((new_fd = open(*formated,
					perm, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
	{
		ft_dprintf(STDERR_FILENO, "mysh: could not open file %s\n", file);
		new_fd = -1;
	}
	free_tab_str(&formated);
	free_tab_str(&tmp);
	return (new_fd);
}

int				check_src_fd(char *input, int default_fd)
{
	int				new_fd;

	new_fd = (ft_isdigit(*input) == FALSE) ? default_fd : ft_atoi(input);
	if (new_fd > MAX_FD)
	{
		ft_dprintf(STDERR_FILENO, "mysh: bad file descriptor [%d]\n", new_fd);
		exit(EXIT_FAILURE);
	}
	return (new_fd);
}
