/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:48:19 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*ft_strjoinc(char *s1, char s2)
{
	char	*str;
	char	*ptr;
	int		i;

	i = 0;
	if ((str = (char *)malloc(ft_strlen(s1) + 2)) == NULL)
		return (NULL);
	ptr = str;
	while (s1[i])
		*ptr++ = s1[i++];
	*ptr++ = s2;
	*ptr++ = '\0';
	return (str);
}

int			printlvl(void)
{
	return (g_lvl);
}

int			get_sh_lvl(t_sh *sh)
{
	int		i;
	char	*tmp;
	char	**av;

	i = -1;
	while (sh->env.env[++i] != NULL)
	{
		if (strncmp(sh->env.env[i], "SHLVL=", 6) == 0)
		{
			g_lvl = (int)(sh->env.env[i][6] - 48) + 1;
			tmp = sh->env.env[i];
			sh->env.env[i] = ft_strjoinc("SHLVL=", g_lvl + 48);
			ft_strdel(&tmp);
			return (g_lvl);
		}
	}
	if (!(av = (char **)malloc(sizeof(char *) * 4)))
		return (2);
	av[0] = ft_strdup("setenv");
	av[1] = ft_strdup("SHLVL");
	av[2] = ft_strdup("2");
	av[3] = NULL;
	ft_setenv(sh, av);
	return (2);
}
