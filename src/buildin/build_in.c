/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 07:26:28 by awyart            #+#    #+#             */
/*   Updated: 2018/02/16 14:21:30 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

const t_op	g_built_in[BUILD_IN_SIZE + 1] =
{
	{"echo", &ft_echo},
	{"cd", &ft_cd},
	{"env", &ft_env},
	{"setenv", &ft_setenv},
	{"unsetenv", &ft_unsetenv},
	{"exit", &ft_exit},
	{NULL, NULL}
};

int			detect_bi(char *cmd, const t_op *cmd_tab)
{
	int		i;
	int		ret;

	i = 0;
	if (cmd == NULL)
		return (-1);
	while (cmd_tab[i].fun_ptr != NULL)
	{
		if ((ret = ft_strcmp(cmd, cmd_tab[i].name)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int			exec_builtin(int index, char *input)
{
	char	**av;
	int		ret;

	av = ft_strsplit(input, ' ');
	ret = g_built_in[index].fun_ptr(g_sh, av);
	free_tab_str(&av);
	return (ret);
}

int			is_builtin(char *input)
{
	int			i;
	char		*cmd_name;

	cmd_name = get_cmd_name(input);
	i = detect_bi(cmd_name, g_built_in);
	free_str(&cmd_name);
	return (i);
}
