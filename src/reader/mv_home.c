#include "header.h"

int	move_end(t_dlist_wrap *wrap)
{
	if (wrap->pos < 0 || wrap->pos >= wrap->size)
		return (0);
	wrap->pos = wrap->size;
	return (1);
}

int	move_home(t_dlist_wrap *wrap)
{
	if (wrap->pos <= 0)
		return (0);
	wrap->pos = 0;
	return (1);
}
