#include "../inc/levenshtein.h"

t_dlist		*ft_hlstnew(t_lev *new)
{
	t_dlist	*child;

	if ((child = (t_dlist *)malloc(sizeof(t_dlist))) == NULL)
		return (NULL);
	child->content = new;
	child->prev = NULL;
	child->next = NULL;
	return (child);
}

t_dlist		*ft_hlstnew_void(void *new)
{
	t_dlist	*child;

	if ((child = (t_dlist *)malloc(sizeof(t_dlist))) == NULL)
		return (NULL);
	child->content = new;
	child->prev = NULL;
	child->next = NULL;
	return (child);
}
