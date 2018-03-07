/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 03:43:21 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 19:13:27 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	**envdup(void)
{
	char	**env;
	int		size;
	int		i;

	size = ft_tablen(g_environ);
	i = 0;
	if (!(env = (char **)ft_memalloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		env[i] = ft_strdup(g_environ[i]);
		i++;
	}
	return (env);
}

int			ft_setupenv(t_environ *env)
{
	if (!(env->env = envdup()))
		return (0);
	env->size = ft_tablen(env->env);
	return (1);
}

char		*get_env_var(char *val, char **environ)
{
	int		size;
	char	*str;
	char	*new;

	size = ft_tablen(environ);
	new = ft_strjoin(val, "=");
	while (size--)
	{
		if ((ft_strncmp(new, environ[size - 1], 5) == 0))
		{
			str = environ[size - 1] + 5;
			return (str);
		}
	}
	ft_strdel(&new);
	return (NULL);
}
