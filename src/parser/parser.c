/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:53:45 by awyart            #+#    #+#             */
/*   Updated: 2018/02/12 16:04:34 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void ft_print_tree(t_btree *btree)
{
	if (btree != NULL)
	{
		ft_print_tree(btree->left);
		if (btree->process)
		{
			dprintf(g_fd, "\ncmd <%s>", btree->process->argv[0]);
			if (btree->process->file)
				dprintf(g_fd, "redir<%d> file <%s>",btree->process->file->type, btree->process->file->name[0]);
		}
		dprintf(g_fd, "\n");
		ft_print_tree(btree->right);
	}
}

int ft_print_parsoutput(t_btree **btree)
{
	int i = 0;

	if (btree != 0)
	{	
		while (btree[i] != NULL)
		{
			ft_print_tree(btree[i]);
			i++;
		}
	}
	return (1);
}

static int count_nb_tree(t_token *token)
{
	int count;

	count = 1;
	while (token != NULL)
	{
		if (token->e_type == SEMICOL)
			count++;
		token = token->next;
	}
	return (count);
}

int 	add_proc(t_btree **btree, t_btree **node, t_token **token, t_process *process)
{
	(*node)->process = process;
	if ((*token))
		(*node)->type = (*token)->e_type;
	if (*btree == NULL)
	{
		if (process == NULL)
			return (1);
		*btree = (*node);
		return (0);
	}
	if (process == NULL)
	{
		if ((*btree)->left != NULL && (*btree)->right == NULL)
		{
			return (1);
		}
		(*node)->left = *btree;
		*btree = *node;
		(*token) = (*token)->next;
		return (0);
	}
	if ((*btree)->right != NULL)
		return (1);
	(*btree)->right = (*node);
	return (0);
}

int 	ft_parser(t_sh *sh)
{
	t_btree	**start_tree = NULL;
	t_btree *node = NULL;
	t_token *token;
	t_process *process = NULL;
	int i = 0;

	ft_print_lexoutput(&(sh->token));
	token = sh->token;
	if (!(start_tree = (t_btree **)ft_memalloc(sizeof(t_btree *) * (count_nb_tree(token) + 1)))) // maybe leaks here
	{
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
		return (0);
	}
	while (token != NULL)
	{
		process = NULL;
		if (!(node = (t_btree *)ft_memalloc(sizeof(t_btree))))
			return (0);
		if (token->e_type == WORD)
			process = ft_new_process(&token);
		if (add_proc(&(start_tree[i]), &node, &token, process))
		{
			ft_dprintf(STDERR_FILENO, "awsh : parse error");
			return (0);
		}
		if (token && token->e_type == SEMICOL)
		{
			token = token->next;
			i++;
		}
	}
	ft_print_parsoutput(start_tree);
	sh->btree = start_tree;
	return (1);
}
