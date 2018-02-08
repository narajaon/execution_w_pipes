#include "../inc/levenshtein.h"

void		list_to_lev_tree(t_dlist **tree_nodes, t_dlist *data_base)
{
	while (data_base)
	{
		add_to_child(tree_nodes, data_base);
		data_base = data_base->next;
	}
}
