#include "../../inc/header.h"

bool		has_env_var(char **env, char *var)
{
	int			var_len;

	var_len = ft_strlen(var);
	while (*env)
	{
		if (cmp_env_var(*env, var, var_len) == 0)
			return (TRUE);
		env++;
	}
	return (FALSE);
}

char		*get_next_dir(char **av, char *prev_dir, t_environ *env)
{
	char		*next_dir;

	next_dir = *av;
	if (*av == NULL)
		next_dir = ft_getenv(env->env, "HOME");
	else if (av[0] != NULL && av[1] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (NULL);
	}
	else if (ft_strcmp(av[0], "-") == 0 || ft_strcmp(av[0], "-1") == 0)
		next_dir = prev_dir;
	if (next_dir == NULL || chdir(next_dir) < 0)
	{
		ft_putstr_fd("cd: can't change directory\n", STDERR_FILENO);
		chdir(prev_dir);
		return (prev_dir);
	}
	return (next_dir);
}

char		*get_cur_dir(char *cur_dir_buff)
{
	char		*tmp;
	int			len;

	if (!(tmp = getcwd(cur_dir_buff, PATH_MAX + 1)))
		return (NULL);
	len = ft_strlen(tmp);
	while (len > 0 && tmp[len] != '/')
		len--;
	if (tmp[len] == '/' && ft_strcmp(tmp, "/") != 0)
		len++;
	tmp = &tmp[len];
	return (tmp);
}

int			ft_cd(t_sh *sh, char **av)
{
	char		*next_dir;

	sh->dir.dir_name = NULL;
	get_cur_dir(sh->dir.cur_dir);
	add_var_to_env(sh, (char *[2]){"OLDPWD", sh->dir.cur_dir});
	if ((next_dir = get_next_dir(&av[1], sh->dir.prev_dir, &sh->env)) == NULL)
	{
		sh->dir.dir_name = get_cur_dir(sh->dir.cur_dir);
		return (1);
	}
	getcwd(sh->dir.prev_dir, PATH_MAX + 1);
	add_var_to_env(sh, (char *[2]){"PWD", sh->dir.prev_dir});
	ft_strcpy(sh->dir.prev_dir, sh->dir.cur_dir);
	sh->dir.dir_name = get_cur_dir(sh->dir.cur_dir);
	return (0);
}
