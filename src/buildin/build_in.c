#include "../inc/header.h"

const t_op	g_build_in[] =
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

int			is_builtin(char **av)
{
	int		i;
	int		ret;

	if ((i = detect_bi(av[0], g_build_in)) < 0)
		return (-1);
	ret = g_build_in[i].fun_ptr(g_sh, av);
	return (ret);
}
