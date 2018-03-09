/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 19:00:19 by awyart            #+#    #+#             */
/*   Updated: 2018/03/09 20:28:06 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
		ICI
		return (NULL);
	}
	hash->cmd = ft_strdup(str);
	hash->path = ft_strdup(path);
	return (tmp);
}

int 			add_in_haslist(t_dlist *new)
{
	t_dlist *list;

	if (g_hash == NULL)
	{
		dprintf(g_fd, "g_hash = new\n");
		g_hash = new;
		return (1);
	}
	list = g_hash;
	while (list != NULL && (list)->next != NULL)
		(list) = (list)->next;
	(list)->next = new;
	new->prev = list;
	new->next = NULL;
	return (1);
}

int 			add_in_path(char *str, char *path)
{
	t_dlist *new;

	dprintf(g_fd, "create_new_hash\n");
	if ((new = create_new_hash(str, path)) == NULL)
		return (-1);
	dprintf(g_fd, "add_in_haslist\n");
	add_in_haslist(new);
	return (0);
}

char 			*get_in_hash(char *str)
{
	t_dlist *list;
	t_hash	*hash;

	list = g_hash;
	while (list != NULL)
	{
		hash = list->content;
		if (ft_strcmp(hash->cmd, str) == 0)
			return (hash->path);
		list = list->next;
	}
	return (NULL);
}

int				ft_hash(t_sh *sh, char **av)
{
	t_hash *hash;
	t_dlist *list;

	(void)av;
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