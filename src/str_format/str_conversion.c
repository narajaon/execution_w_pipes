#include "../../inc/header.h"

char		**ft_list_to_tab(t_dlist *list)
{
	char	**av;
	int		lst_size;
	int		i;

	i = 0;
	lst_size = hlst_size(list);
	av = (char **)malloc(sizeof(char *) * (lst_size + 1));
	while (list)
	{
		av[i++] = list->content;
		list = list->next;
	}
	av[i] = NULL;
	return (av);
}
