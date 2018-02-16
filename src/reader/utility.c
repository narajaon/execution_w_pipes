#include "header.h"

int			ft_count_string(t_dlist *lst)
{
	t_dlist	*list;
	int		count;

	count = 0;
	list = lst;
	while (list != NULL)
	{
		count++;
		list = list->next;
	}
	return (count);
}
