/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 07:46:17 by awyart            #+#    #+#             */
/*   Updated: 2018/02/21 16:32:16 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			ft_unsetenv(t_sh *sh, char **var)
{
	int			var_len;

	if (var[1] == NULL)
		return (1);
	if (var[1] != NULL && var[2] != NULL)
	{
		ft_putstr("unsetenv: too many arguments\n");
		return (1);
	}
	var_len = ft_strlen(var[1]);
	sh->env.env = tab_str_remove(sh->env.env, &cmp_env_var, var[1], var_len);
	return (0);
}
