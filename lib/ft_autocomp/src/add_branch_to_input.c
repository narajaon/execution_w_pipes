#include "../inc/levenshtein.h"

void		add_branch_to_input(t_dlist **input, t_dlist *branch)
{
	t_lev		*new;
	t_dlist		*tmp;

	if (branch == NULL)
		return ;
	if (*input == NULL)
	{
		tmp = *input;
		while (branch)
		{
			new = branch->content;
			ft_hlstadd_back(input, branch);
			branch = new->child;
		}
	}
	else
		add_branch_to_input(&(*input)->next, branch);
}
