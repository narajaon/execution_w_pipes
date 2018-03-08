/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_semicol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:20:39 by awyart            #+#    #+#             */
/*   Updated: 2018/03/08 12:06:25 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		hl_print_str(t_dlist *list)
{
	if (list == NULL)
		return ;
	ft_printf("-> |%s|\n", list->content);
}

int			skip_quotes(char *str, char quote)
{
	int		i;

	i = 0;
	if (*str == quote)
	{
		while (str[++i] && str[i] != quote)
		{
			if (str[i] == '\\' && str[i + 1] == '\"')
				i++;
		}
	}
	return (i);
}

char		*split_by_token(t_dlist **procs, char *input, char token)
{
	int			i;
	char		*sub;

	i = 0;
	while (input[i] && input[i] != token)
	{
		if (input[i] == '\\' && input[i + 1] == token)
			i++;
		i += skip_quotes(&input[i], '\"');
		i += skip_quotes(&input[i], '\'');
		if (input[i] == '\0')
			break ;
		i++;
	}
	if (i == 0)
		return (&input[i + 1]);
	sub = ft_strsub(input, 0, i);
	ft_hlstadd_back_void(procs, sub);
	if (input[i] == '\0')
		return (&input[i]);
	return (&input[i + 1]);
}

t_dlist		*init_proc_list(char *input, char token)
{
	t_dlist		*procs;

	procs = NULL;
	while (*input != '\0')
		input = split_by_token(&procs, input, token);
	return (procs);
}
