/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 08:53:22 by awyart            #+#    #+#             */
/*   Updated: 2018/01/22 10:34:46 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char *ft_new_cmd(char *path, char *cmd)
{
	char *new;
	int s1;
	int s2;
	int k;

	s1 = ft_strlen(path);
	s2 = ft_strlen(cmd);
	dprintf(g_fd, "path <%s> cmd <%s>\n", path, cmd);
	if (!(new = (char *)malloc(sizeof(char) * (s1 + s2 + 1))))
	{
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
		return (NULL);
	}
	k = s1;
	while (s1 >= 0)
	{
		new[s1] = path[s1];
		s1--;
	}
	new[k] = '/';
	while (s2 >= 0)
	{
		new[k + 1 + s2] = cmd[s2];
		s2--;
	}
	return (new);
}

static int		ft_exist(char *str, char *place)
{
	DIR				*dir;
	struct dirent	*ret;

	dir = opendir(place);
	if (dir == NULL)
		return (0);
	while ((ret = readdir(dir)) > 0)
	{
		if (ft_strcmp(ret->d_name, str) == 0)
		{
			(void)closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

char 	*ft_create_cmd(t_sh *sh, t_process *process)
{
	char *paths;
	char **list_path;
	char *tmp = NULL;
	int i;
	
	i = 0;
	/*if (tmp = checkin_hashset(process->argv[0]) != NULL)
		return (tmp);*/
	paths = get_env_var("PATH", sh->env.env);
	list_path = ft_strsplit(paths, ':');
	while (list_path[i])
	{
		if (ft_exist(process->argv[0], list_path[i]))
		{
			tmp = ft_new_cmd(list_path[i], process->argv[0]);
			free_tab(list_path);
			return (tmp);
		}
		i++;
	}
	free_tab_str(&list_path);
	tmp = ft_strdup(process->argv[0]);
	return (tmp);
}
