#include "../../inc/header.h"

int				exec_prog(t_dlist *curr, int *save)
{
	int			status;
	char		**split;
	char		**bin_paths;
	char		*path;

	status = 0;
	if (!(split = extract_redir(curr, save)))
		exit(EXIT_FAILURE);
	//pas opti, devrait se faire a l'initialisation
	if (!(bin_paths = ft_strsplit(ft_getenv(g_sh->env.env, "PATH"), ':')))
	{
		ft_putstr_fd("PATH not valid\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	path = check_bin(bin_paths, split[0]);
	if (path == NULL)
	{
		if ((is_binary_file(split[0]) == TRUE) &&
				(is_valid_path(split[0]) == TRUE))
			path = split[0];
		else
		{
			ft_putstr_fd("command not found\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
	return (execve(path, split, g_sh->env.env));
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
		if (cmd_id == B_CD)
			status = save_builtin_stdio(cmd_id, curr);
		else if (curr->next == NULL)
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
	cmd_id = is_builtin(curr->content);
	g_lvl++;
	if ((g_cur_pid = fork()) == 0)
	{
		status = exec_in_child(curr, cpfd, pfd, cmd_id);
		exit(EXIT_SUCCESS);
	}
	else
		exec_in_parent(curr, cpfd, pfd, cmd_id);
	g_lvl--;
	return (status);
}
