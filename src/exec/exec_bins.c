/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/20 16:36:49 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int				exec_prog(t_dlist *curr, int *save)
{
	char		**split;
	char		*path_dirs;
	char		*path;

	if (!(split = extract_redir(curr, save)))
		exit(EXIT_FAILURE);
	split = fmt_input_quote(split);
	path_dirs = ft_getenv(g_sh->env.env, "PATH");
	if ((path = get_in_hash(split[0])) != NULL)
	{
		if (path && access(path, X_OK) != 0)
			exit(exit_error("permission denied\n", EXIT_FAILURE, split[0]));
		execve(path, split, g_sh->env.env);
	}
	else if (is_binary_file(split[0]) == TRUE)
	{
		if (is_valid_path(split[0]) == TRUE)
		{
			execve(split[0], split, g_sh->env.env);
		}
		exit_error("execution denied\n", EXIT_FAILURE, split[0]);
	}
	return (exit_error("command not found\n", EXIT_FAILURE, split[0]));
}

int				exec_in_child(t_dlist *curr, int *cpfd, int *pfd, int cmd_id)
{
	int			status;
	int			save[2];

	status = 0;
	if (curr->next != NULL)
		dup2(cpfd[1], STDOUT_FILENO);
	if (curr->prev != NULL)
		dup2(pfd[0], STDIN_FILENO);
	save[1] = dup(cpfd[1]);
	close_fd(pfd);
	close_fd(cpfd);
	if (cmd_id < 0)
		status = exec_prog(curr, save);
	if (curr->next != NULL)
		status = exec_builtin(cmd_id, curr, save);
	return (status);
}

int				exec_in_parent(t_dlist *curr, int *cpfd, int *pfd, int cmd_id)
{
	int			status;

	status = 0;
	close_fd(pfd);
	if (cmd_id >= 0)
	{
		if (curr->next == NULL)
			status = save_builtin_stdio(cmd_id, curr);
	}
	if (curr->next != NULL)
		status = pipe_processes(curr->next, cpfd);
	close_fd(cpfd);
	return (status);
}

int				pipe_processes(t_dlist *curr, int *pfd)
{
	int			status;
	int			cpfd[2];
	int			cmd_id;

	status = 0;
	pipe(cpfd);
	if ((cmd_id = is_builtin(curr->content)) >= 0 && curr->next == NULL)
		return (status = exec_in_parent(curr, cpfd, pfd, cmd_id));
	hash_check(curr->content);
	g_lvl++;
	if ((g_cur_pid = fork()) == 0)
	{
		status = exec_in_child(curr, cpfd, pfd, cmd_id);
		exit(EXIT_SUCCESS);
	}
	else
	{
		exec_in_parent(curr, cpfd, pfd, cmd_id);
	}
	g_lvl--;
	return (status);
}
