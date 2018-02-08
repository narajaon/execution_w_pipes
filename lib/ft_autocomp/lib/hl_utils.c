#include "../inc/levenshtein.h"

t_dlist		*hlget_last(t_dlist *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL && list->next->next != NULL)
		list = list->next;
	return (list);
}

int			hlst_size(t_dlist *list)
{
	int		i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void		free_hlist(t_dlist **list)
{
	t_dlist		*to_free;
	t_dlist		*next;

	to_free = *list;
	while (to_free)
	{
		next = to_free->next;
		free(to_free->content);
		free(to_free);
		to_free = to_free->next;
	}
}
