/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:46:58 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:39:34 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char			*get_var_val(char *var)
{
	char	*val;

	val = var;
	while (*val && *val != '=')
		val++;
	if (*val == '=')
		val++;
	return (val);
}

int				cmp_env_var(char *var, char *to_cmp, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n && (var[i] || to_cmp[i]))
	{
		if (var[i] - to_cmp[i] != 0)
			return (var[i] - to_cmp[i]);
		i++;
	}
	if (to_cmp[i] == '\0' && var[i] == '=')
		return (0);
	return (-1);
}

char			*ft_getenv(char **env, char *var)
{
	char		*value;
	int			var_len;

	value = NULL;
	if (env == NULL)
		return (NULL);
	var_len = ft_strlen(var);
	while (*env)
	{
		if ((cmp_env_var(*env, var, var_len)) == 0)
			break ;
		env++;
	}
	if (*env)
		value = get_var_val(*env);
	return (value);
}

static void		ft_print_tab_fd(char **tab_p)
{
	int			i;

	i = 0;
	while (tab_p != NULL && tab_p[i] != NULL)
	{
		ft_putendl_fd(tab_p[i], STDOUT_FILENO);
		i++;
	}
}

int				ft_env(t_sh *sh, char **av)
{
	if (av[1] == 0)
		ft_print_tab_fd(sh->env.env);
	else
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
	return (0);
}
