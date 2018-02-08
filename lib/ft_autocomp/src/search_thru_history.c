#include "../inc/levenshtein.h"

t_dlist		*get_branch(t_dlist *input, t_dlist *data_base)
{
	t_dlist			*branch;
	t_lev			*node;
	char			*c;

	node = NULL;
	branch = data_base;
	if (data_base != NULL && input != NULL)
	{
		while (data_base)
		{
			node = data_base->content;
			c = input->content;
			if (*c == node->content)
			{
				node = data_base->content;
				branch = node->child;
				return (get_branch(input->next, branch));
			}
			data_base = data_base->next;
		}
		branch = NULL;
	}
	return (branch);
}

t_dlist		*history_up(t_dlist *word, t_dlist *cur_branch, t_dlist *history)
{
	t_dlist		*res;
	t_dlist		*branch;

	res = NULL;
	if (cur_branch == NULL)
	{
		branch = get_branch(word, history);
		tree_to_list(NULL, branch, &res);
		return (res);
	}
	if (cur_branch->next == NULL)
		return (cur_branch);
	return (cur_branch->next);
}

t_dlist		*history_down(t_dlist *word, t_dlist *cur_branch,
		t_dlist *history)
{
	if (cur_branch == NULL)
		return (NULL);
	if (cur_branch->prev == NULL)
		return (NULL);
	return (cur_branch->prev);
}
