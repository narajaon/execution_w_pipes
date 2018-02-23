#include "../inc/header.h"

t_op	g_built_in[BUILD_IN_SIZE + 1] =
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

int			is_builtin(char *input)
{
	int			i;
	char		*cmd_name;

	cmd_name = get_cmd_name(input);
	i = detect_bi(cmd_name, g_built_in);
	free_str(&cmd_name);
	return (i);
}
