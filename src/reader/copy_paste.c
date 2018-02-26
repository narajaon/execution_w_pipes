#include "header.h"

int			cut_list(t_dlist_wrap *wrap)
{
	t_dlist		*saved;
	int			i;

	i = -1;
	saved = wrap->head;
	while (++i < wrap->pos && saved)
		saved = saved->next;
	if (saved == NULL)
		return (0);
	if (saved->prev != NULL)
		saved->prev->next = NULL;
	else
	{
		saved = wrap->head;
		wrap->head = NULL;
	}
	wrap->size -= ft_count_string(saved);
	free_hlist(&wrap->yanked);
	wrap->yanked = saved;
	return (1);
}

static void	resize(t_dlist_wrap *wrap, int nbr)
{
	wrap->pos += nbr;
	wrap->size += nbr;
}

int			paste_list(t_dlist_wrap *wrap)
{
	t_dlist	*yank_dup;
	t_dlist	*part_1;
	t_dlist	*part_2;

	if (wrap->yanked == NULL)
		return (0);
	yank_dup = ft_dlist_dup(wrap->yanked, sizeof(t_chr));
	part_1 = wrap->head;
	part_2 = cur_list(wrap);
	if (part_2 != NULL)
		part_2 = part_2->next;
	resize(wrap, hlst_size(yank_dup));
	if (part_2 != NULL && part_2->prev != NULL)
	{
		part_2->prev->next = NULL;
		ft_hlstadd_back(&part_1, yank_dup);
	}
	else if (part_2 != NULL && part_2->prev == NULL)
		part_1 = yank_dup;
	else
		part_2 = yank_dup;
	if (part_2 != NULL)
		ft_hlstadd_back(&part_1, part_2);
	wrap->head = part_1;
	return (1);
}
