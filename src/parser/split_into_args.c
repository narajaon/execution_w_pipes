/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:53:45 by awyart            #+#    #+#             */
/*   Updated: 2018/03/20 18:07:35 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

char			*get_next_arg(t_dlist **arg, t_dlist **redirs, char *input)
{
	char		*skip;

	skip = NULL;
	while (*input)
	{
		while (*input != '\0' && ft_isspace(*input) == TRUE)
			input++;
		if ((skip = is_redir(redirs, input)) != NULL)
			input = skip;
		else if ((skip = is_arg(arg, input)) != NULL)
			input = skip;
	}
	return (input);
}

t_dlist			*parse_arg_redirs(char *input)
{
	t_dlist		*arg;
	t_dlist		*redirs;
	t_dlist		*to_free;

	arg = NULL;
	redirs = NULL;
	while (*input != '\0')
		input = get_next_arg(&arg, &redirs, input);
	to_free = redirs;
	while (redirs != NULL)
	{
		if (do_redirs(redirs) == EXIT_FAILURE)
		{
			free_hlist(&arg);
			free_hlist(&to_free);
			return (NULL);
		}
		redirs = redirs->next;
	}
	free_hlist(&to_free);
	return (arg);
}

char			**extract_redir(t_dlist *curr, int *save)
{
	t_dlist		*av_lst;
	char		**av_str;

	if (!(av_lst = parse_arg_redirs(curr->content)))
		return (NULL);
	av_str = ft_list_to_tab(av_lst);
	free_hlist_not_content(&av_lst);
	if (save != NULL)
		close(save[1]);
	return (av_str);
}
