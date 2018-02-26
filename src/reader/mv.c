#include "header.h"

int	move_right(t_dlist_wrap *wrap)
{
	if (wrap->pos >= wrap->size)
		return (0);
	wrap->pos++;
	return (1);
}

int	move_left(t_dlist_wrap *wrap)
{
	if (wrap->pos <= 0)
		return (0);
	wrap->pos--;
	return (1);
}
