/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:46:58 by awyart            #+#    #+#             */
/*   Updated: 2018/03/08 11:51:58 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int			exec_builtin(int index, t_dlist *curr, int *save)
{
	char	**av;
	char	**to_free;
	int		ret;

	if (!(av = extract_redir(curr, save)))
		return (-1);
	to_free = fmt_input_quote(av);
	ret = g_built_in[index].fun_ptr(g_sh, to_free);
	free_tab_str(&to_free);
	free_tab_str(&av);
	return (ret);
}

int			save_builtin_stdio(int index, t_dlist *curr)
{
	int		ret;
	int		saved_fd[3];

	init_stdio(saved_fd);
	ret = exec_builtin(index, curr, g_sh->stdio);
	dup_stdio(saved_fd);
	close(saved_fd[0]);
	close(saved_fd[1]);
	close(saved_fd[2]);
	return (ret);
}
