#include "../inc/header.h"

int			exec_builtin(int index, t_dlist *curr, int *save)
{
	char	**av;
	int		ret;

	if (!(av = extract_redir(curr, save)))
		return (-1);
	ret = g_built_in[index].fun_ptr(g_sh, av);
	free_tab_str(&av);
	return (ret);
}

int			save_builtin_stdio(int index, t_dlist *curr)
{
	int		ret;
	int		saved_fd[3];

	saved_fd[0] = dup(STDIN_FILENO);
	saved_fd[1] = dup(STDOUT_FILENO);
	saved_fd[2] = dup(STDERR_FILENO);
	ret = exec_builtin(index, curr, 0);
	dup2(saved_fd[0], STDIN_FILENO);
	dup2(saved_fd[1], STDOUT_FILENO);
	dup2(saved_fd[2], STDERR_FILENO);
	close(saved_fd[0]);
	close(saved_fd[1]);
	close(saved_fd[2]);
	return (ret);
}
