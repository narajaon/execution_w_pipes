/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:46:58 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:40:21 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char			*skip_cmd_name(t_dlist **arg, char *input)
{
	int			i;
	char		*sub;

	i = 0;
	while (*input != '\0' && ft_isspace(*input) == TRUE)
		input++;
	if (*input == '\"')
		i += skip_quotes(input, '\"') + 1;
	else if (*input == '\'')
		i += skip_quotes(input, '\"') + 1;
	else
	{
		while (input[i] != '\0' && ft_isspace(input[i]) == FALSE)
			i++;
	}
	sub = ft_strsub(input, 0, i);
	ft_hlstadd_back_void(arg, sub);
	return (&input[i]);
}

int				is_file_redir(char *input)
{
	int			i;

	i = 0;
	if (*input == '&')
	{
		if (*(input + 1) == '-')
			return (i + 2);
		while (input[++i] && ft_isdigit(input[i]) == TRUE)
			;
		return (i);
	}
	while (input[i] != '\0' && ft_isspace(input[i]) == TRUE)
		i++;
	while (input[i] != '\0' && ft_isspace(input[i]) == FALSE)
		i++;
	return (i);
}

char			*is_redir(t_dlist **redir, char *input)
{
	int			i;
	int			type;
	char		*sub;

	i = 0;
	while (input[i] && ft_isdigit(input[i]) == TRUE)
		i++;
	while (input[i] && ft_isspace(input[i]) == TRUE)
		i++;
	if ((type = get_redir(&input[i])) >= 0)
	{
		i += (type == R_LEFT || type == R_RIGHT) ? 1 : 2;
		i += is_file_redir(&input[i]);
		sub = ft_strsub(input, 0, i);
		ft_hlstadd_back_void(redir, sub);
		return (&input[i]);
	}
	return (NULL);
}

char			*is_arg(t_dlist **arg, char *input)
{
	int			i;
	char		*sub;

	i = 0;
	if ((i += skip_quotes(&input[i], '\"')) != 0)
	{
		sub = ft_strsub(input, 0, i + 1);
		ft_hlstadd_back_void(arg, sub);
		return (&input[i + 1]);
	}
	if ((i += skip_quotes(&input[i], '\'')) != 0)
	{
		sub = ft_strsub(input, 0, i + 1);
		ft_hlstadd_back_void(arg, sub);
		return (&input[i + 1]);
	}
	while (input[i] && ft_isspace(input[i]) == FALSE)
		i++;
	if (i == 0)
		return (input);
	sub = ft_strsub(input, 0, i);
	ft_hlstadd_back_void(arg, sub);
	return (&input[i]);
}
