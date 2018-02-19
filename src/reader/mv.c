#include "header.h"

int			move_right(t_dlist_wrap *wrap)
{
	if (wrap->pos >= wrap->size)
		return (0);
	wrap->pos++;
	return (1);
}

int			move_left(t_dlist_wrap *wrap)
{
	if (wrap->pos <= 0)
		return (0);
	wrap->pos--;
	return (1);
}

int			move_end(t_dlist_wrap  *wrap)
{
	if (wrap->pos < 0 || wrap->pos >= wrap->size)
		return (0);
	wrap->pos = wrap->size;
	return (1);
}

int			move_home(t_dlist_wrap  *wrap)
{
	if (wrap->pos <= 0)
		return (0);
	wrap->pos = 0;
	return (1);
}

int 		move_sup(t_dlist_wrap *wrap)
{
	int col;

	col = wrap->col;
	if (wrap->pos < col)
		return (0);
	wrap->pos -= col;
	if (wrap->pos < 0)
		wrap->pos = 0;
	return (1);
}

int 		move_sdown(t_dlist_wrap *wrap)
{
	int col;

	col = wrap->col;
	if ((wrap->size % col) <= (wrap->pos % col))
		return (0);
	wrap->pos += col;
	if (wrap->pos >= wrap->size)
		wrap->pos = wrap->size;
	return (1);
}
