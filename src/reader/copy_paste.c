#include "../../inc/header.h"

int		cut_list(t_dlist_wrap *wrap)
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
	free_hlist(&wrap->yanked);
	wrap->yanked = saved;
	return (1);
}

int		paste_list(t_dlist_wrap *wrap)
{
	if (wrap->yanked == NULL)
		return (0);
		write(STDIN_FILENO, wrap->yanked, hlst_size(wrap->yanked));
	return (1);
	// yank_dup = ft_dlist_dup(wrap->yanked, sizeof(t_chr));
	// part_1 = wrap->head;
	// part_2 = wrap->cursor;
	// wrap->pos += hlst_size(yank_dup);
	// wrap->cursor = part_2;
	// if (part_2 != NULL && part_2->prev != NULL)
	// {
	// 	part_2->prev->next = NULL;
	// 	ft_hlstadd_back(&part_1, yank_dup);
	// }
	// else if (part_2 != NULL && part_2->prev == NULL)
	// 	part_1 = yank_dup;
	// else
	// {
	// 	part_2 = yank_dup;
	// 	wrap->cursor = NULL;
	// }
	// if (part_2 != NULL)
	// 	ft_hlstadd_back(&part_1, part_2);
	// wrap->head = part_1;
	// wrap->last = ft_dlist_last(wrap->head);
}
