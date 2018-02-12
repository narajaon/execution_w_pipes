/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 07:26:28 by awyart            #+#    #+#             */
/*   Updated: 2018/02/12 15:05:04 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_op	g_build_in[] =
{
	{"echo", B_ECHO, &ft_echo},
	{"cd", B_CD, &ft_cd},
	{"env", B_ENV, &ft_env},
	{"setenv", B_SETENV, &ft_setenv},
	{"unsetenv", B_UNSETENV, &ft_unsetenv},
	{"exit", B_EXIT, &ft_exit}
};

int		detect_bi(char *str)
{
	int			i;

	i = -1;
	while (++i < BUILD_IN_SIZE - 1)
	{
		if (ft_strcmp(str, g_build_in[i].cmd) == 0)
			return (g_build_in[i].type);
	}
	return (B_NONE);
}

int		ft_exec_build_in(t_sh *sh, t_process *process)
{
	int			(*ptr)();
	int			ret;

	ptr = g_build_in[process->bi - 1].f;
	ret = ptr(sh, process->argv);
	return (ret);
}
