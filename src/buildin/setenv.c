#include "../../inc/header.h"

char		**tab_str_add(char **base, char *to_add)
{
	char		**res;
	char		**to_free;
	int			i;
	int			size;

	i = 0;
	if (base == NULL || *base == NULL)
		return (NULL);
	size = ft_tablen(base) + 2;
	to_free = base;
	if (!(res = (char **)malloc(sizeof(char *) * size)))
		return (NULL);
	while (*base)
	{
		res[i++] = ft_strdup(*base);
		base++;
	}
	res[i++] = to_add;
	res[i] = NULL;
	free_tab_str(&to_free);
	return (res);
}

char		**tab_str_remove(char **base, int (*cmp)(), char *to_cmp,
		size_t limit)
{
	char		**res;
	char		**tab_tmp;
	int			i;
	int			size;

	i = 0;
	if (base == NULL || *base == NULL)
		return (NULL);
	size = ft_tablen(base) + 1;
	tab_tmp = base;
	if (!(res = (char **)ft_memalloc(sizeof(char *) * size)))
		return (NULL);
	while (*base)
	{
		if (cmp(*base, to_cmp, limit) != 0)
			res[i++] = ft_strdup(*base);
		base++;
	}
	res[i] = NULL;
	free_tab_str(&tab_tmp);
	return (res);
}

char		*add_eq_between(char **arg)
{
	char		*join;
	char		*str_tmp;

	join = ft_strjoin(arg[0], "=");
	if (arg[1] != NULL)
	{
		str_tmp = join;
		join = ft_strjoin(join, arg[1]);
		free_str(&str_tmp);
	}
	return (join);
}

void		add_var_to_env(t_sh *sh, char **var)
{
	char		*res;
	int			var_len;

	var_len = ft_strlen(var[0]);
	res = add_eq_between(var);
	sh->env.env = tab_str_remove(sh->env.env, &cmp_env_var, var[0], var_len);
	sh->env.env = tab_str_add(sh->env.env, res);
}

int			ft_setenv(t_sh *sh, char **av)
{
	if (av[1] == NULL)
	{
		ft_env(sh, av);
		return (0);
	}
	if (av[1] != NULL && av[2] != NULL && av[3] != NULL)
	{
		ft_putstr("setenv: Too many arguments\n");
		return (-1);
	}
	add_var_to_env(sh, &av[1]);
	return (0);
}
