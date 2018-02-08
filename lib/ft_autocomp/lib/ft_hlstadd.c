#include "../inc/levenshtein.h"

void		ft_hlstadd(t_dlist **alst, t_dlist *new)
{
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	new->next = *alst;
	(*alst)->prev = new;
	*alst = new;
}

void		ft_hlstadd_void(t_dlist **alst, void *new)
{
	t_dlist		*node;

	node = ft_hlstnew_void(new);
	if (*alst == NULL)
	{
		*alst = node;
		return ;
	}
	node->next = *alst;
	(*alst)->prev = node;
	*alst = node;
}
