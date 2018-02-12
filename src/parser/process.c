/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:24:25 by awyart            #+#    #+#             */
/*   Updated: 2018/02/12 15:39:40 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int ft_count_av(t_token *token)
{
	int i;

	i = 0;
	while (token != NULL && token->e_type == WORD)
	{
		i++;
		token = token->next;
	}
	return (i);
};


static int is_redir(int type)
{
	if (type == LREDIR || type == RSREDIR || type == HEREDOC || type == RDREDIR)
		return (1);
	return (0);
}

static int handle_prep_redir(t_process **process, t_token **token)
{
	int i;

	i = 0;
	while ((*token) && (*token)->e_type == IO_NUMBER)
	{
		//ajouter qqchose pour gerer le bastringue
		(*token) = (*token)->next;
	}
	while ((*process)->file != NULL)
		(*process)->file = (*process)->file->next;
	if (!((*process)->file = (t_redir *)ft_memalloc(sizeof(t_redir))))
		return (0);
	(*process)->file->type = (*token)->e_type;
	(*token) = (*token)->next;
	while ((*token) && (*token)->e_type == WORD)
	{
		if (!((*process)->file->name = (char **)ft_memalloc(sizeof(char *) * (ft_count_av((*token)) + 1))))
			return (0);
		(*process)->file->name[i++] = spe_strdup((*token));
		(*token) = (*token)->next;
	}
	if ((*token) == NULL)
		(*process)->last = 1;
	return (1);
}

t_process *ft_new_process(t_token **token)
{
	t_process	*process;
	int			i;


	if (!(process = ft_memalloc(sizeof(t_process))))
		return (NULL);
	//dprintf(g_fd, "\nbonjour00\n");
	if (!(process->argv = (char **)ft_memalloc(sizeof(char *) * (ft_count_av((*token)) + 1))))
		return (NULL);
	i = 0;
	//dprintf(g_fd, "\nbonjour01\n");
	while ((*token) != NULL && (*token)->e_type == WORD)
	{
		process->argv[i++] = spe_strdup((*token));
		(*token) = (*token)->next;
	}
	//dprintf(g_fd, "\nbonjour02\n");
	if (*token)
	{
		//dprintf(g_fd, "\nbonjour03\n");
		while ((*token) != NULL && (*token)->e_type == IO_NUMBER)
		{
			//ajouter qqchose pour gerer le bastringue
			(*token) = (*token)->next;
		}
		//dprintf(g_fd, "\nbonjour04\n");
	}
	while ((*token) && is_redir((*token)->e_type))
		handle_prep_redir(&process, token);
	//dprintf(g_fd, "\nbonjour05\n");
	process->argv[i] =  NULL;
	//dprintf(g_fd, "\nbonjour051\n");
	//process->bi = detect_bi(process->argv[0]);
	//dprintf(g_fd, "\nbonjour052\n");
	process->status = 0;
	//dprintf(g_fd, "\nbonjour06\n");
	return (process);
}


// t_process *ft_new_process(t_token *token)
// {
// 	t_process	*process;
// 	char		**argv;
// 	int			i;

// 	if (!(process = ft_memalloc(sizeof(t_process))))
// 		return (NULL);
// 	if (!(argv = (char **)ft_memalloc(sizeof(char *) * (ft_count_av(token) + 1))))
// 		return (NULL);
// 	i = 0;
// 	while (token != NULL && token->e_type == WORD)
// 	{
// 		argv[i] = spe_strdup(token);
// 		i++;
// 		token = token->next;
// 	}	
// 	argv[i] = NULL;
// 	process->bi = B_NONE;
// 	process->cmd = NULL;
// 	process->argv = argv;
// 	process->next = NULL;
// 	return (process);
// }
