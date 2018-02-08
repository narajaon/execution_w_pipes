#include "../inc/levenshtein.h"

void		print_hlst_content(t_dlist *list)
{
	char	*c;
	t_chr	*content;

	content = list->content;
	printf("|%c|", content->c);
}

void		hl_print_next(t_dlist *list, void (*print)())
{
	while (list)
	{
		print(list);
		list = list->next;
	}
}
