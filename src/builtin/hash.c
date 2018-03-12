/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 19:00:19 by awyart            #+#    #+#             */
/*   Updated: 2018/03/12 16:51:22 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void 			hash_check(char *str)
{
	char		*cmd_name;
	char 		*path;
	char		**bin_paths;
	char		*path_dirs;

	cmd_name = get_cmd_name(str);
	path = NULL;
	path_dirs = NULL;
	if ((path = get_in_hash(cmd_name)) == NULL)
	{
		path_dirs = ft_getenv(g_sh->env.env, "PATH");
		if (!(bin_paths = ft_strsplit(path_dirs, ':')))
			exit_error("PATH not valid\n", EXIT_FAILURE, NULL);
		if (path != NULL)
			ft_strdel(&path);
		path = check_bin(bin_paths, cmd_name);
		if (path != NULL)
			add_in_path(cmd_name, path);
		free_tab_str(&bin_paths);
		ft_strdel(&path);
	}
	else
		ft_strdel(&path);
	ft_strdel(&cmd_name);
}

t_dlist			*create_new_hash(char *str, char *path)
{
	t_dlist	*tmp;
	t_hash *hash;

	hash = ft_memalloc(sizeof(t_hash));
	tmp = ft_dlist_create((void *)(hash));
	if (hash == NULL || tmp == NULL)
	{
		ft_memdel((void **)&hash);
		ft_memdel((void **)&tmp);
		return (NULL);
	}
	hash->cmd = ft_strdup(str);
	hash->path = ft_strdup(path);
	return (tmp);
}

int 			add_in_path(char *str, char *path)
{
	t_dlist *new;

	if ((new = create_new_hash(str, path)) == NULL)
		return (-1);
	ft_hlstadd_back(&g_sh->hash, new);
	return (0);
}

char 			*get_in_hash(char *str)
{
	t_dlist *list;
	t_hash	*hash;

	list = g_sh->hash;
	while (list != NULL)
	{
		hash = list->content;
		if (ft_strcmp(hash->cmd, str) == 0)
			return (ft_strdup(hash->path));
		list = list->next;
	}
	return (NULL);
}

int				ft_hash(t_sh *sh, char **av)
{
	t_hash	*hash;
	t_dlist	*list;

	if (av[1] != NULL)
	{
		ft_dprintf(STDERR_FILENO, "FABIEN JE SAIS OU TU TE CACHES\n");
		return (0);
	}
	list = sh->hash;
	hash = NULL;
	if (list == NULL)
	{
		ft_dprintf(STDERR_FILENO, "No binary found in cache\n");
		return (0);
	}
	ft_dprintf(STDOUT_FILENO, "Les Binaires précache sont :\n");
	while (list != NULL)
	{
		hash = list->content;
		ft_dprintf(STDOUT_FILENO, "cmd [%s] : path [%s]\n", hash->cmd, hash->path);
		list = list->next;
	}
	return (1);
}