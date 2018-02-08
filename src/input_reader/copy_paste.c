#include "../../inc/header.h"

t_dlist		*cut_list(t_dlist_wrap *wrap, t_sh *sh)
{
	t_dlist		*saved;
	int			i;

	i = -1;
	saved = wrap->head;
	while (++i < wrap->pos && saved)
		saved = saved->next;
	if (saved == NULL)
		return (NULL);
	if (saved->prev != NULL)
	{
		saved->prev->next = NULL;
		wrap->last = saved->prev;
		wrap->cursor = wrap->last->next;
	}
	else
	{
		saved = wrap->head;
		wrap->head = NULL;
		wrap->last = NULL;
		wrap->cursor = NULL;
	}
	free_hlist(&wrap->yanked);
	wrap->yanked = saved;
	sh->offset = 0;
	return (saved);
}

void		paste_list(t_dlist_wrap *wrap, t_sh *sh)
{
	t_dlist		*part_1;
	t_dlist		*part_2;
	t_dlist		*yank_dup;

	if (wrap->yanked == NULL)
		return ;
	yank_dup = ft_dlist_dup(wrap->yanked, sizeof(t_chr));
	part_1 = wrap->head;
	part_2 = wrap->cursor;
	wrap->pos += hlst_size(yank_dup);
	wrap->cursor = part_2;
	if (part_2 != NULL && part_2->prev != NULL)
	{
		part_2->prev->next = NULL;
		ft_hlstadd_back(&part_1, yank_dup);
	}
	else if (part_2 != NULL && part_2->prev == NULL)
		part_1 = yank_dup;
	else
	{
		part_2 = yank_dup;
		wrap->cursor = NULL;
	}
	if (part_2 != NULL)
		ft_hlstadd_back(&part_1, part_2);
	wrap->head = part_1;
	wrap->last = ft_dlist_last(wrap->head);
	sh->offset = 0;
}
