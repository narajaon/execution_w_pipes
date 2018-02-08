#include "../inc/autocompletion.h"
#include "../inc/levenshtein.h"

t_dlist			*new_hlist_dlist(t_dlist *list)
{
	t_dlist		*new;

	if ((new = (t_dlist *)malloc(sizeof(t_dlist))) == NULL)
		return (NULL);
	new->content = list;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_dlist			*hlist_cpy(t_dlist *tree)
{
	t_dlist		*result;
	t_lev		*lev;
	t_lev		*cont;

	result = NULL;
	while (tree)
	{
		cont = tree->content;
		lev = (t_lev *)malloc(sizeof(t_lev));
		lev->content = cont->content;
		lev->child = NULL;
		ft_hlstadd_back_void(&result, lev);
		tree = tree->next;
	}
	return (result);
}

t_dlist			*get_child(t_dlist *node)
{
	t_lev		*content;

	if (node == NULL)
		return (NULL);
	content = node->content;
	return (content->child);
}

static t_chr	*new_chr(char c, int is_escaped)
{
	t_chr		*new;

	new = (t_chr *)malloc(sizeof(t_chr));
	new->c = c;
	new->is_escaped = is_escaped;
	return (new);
}

void			tree_to_list(t_dlist *prev, t_dlist *cur, t_dlist **res)
{
	t_lev		*content;
	t_dlist		*list;
	t_chr		*schr;

	list = NULL;
	if (prev != NULL)
		list = hlist_cpy(prev);
	while (cur)
	{
		content = cur->content;
		if (cur->next != NULL)
			tree_to_list(list, cur->next, res);
		schr = new_chr(content->content, '0');
		ft_hlstadd_back_void(&list, schr);
		cur = content->child;
	}
	ft_hlstadd_void(res, list);
}
