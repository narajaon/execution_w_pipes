#include "../inc/levenshtein.h"

void		free_str(char **str)
{
	if (*str == NULL)
		return ;
	free(*str);
	*str = NULL;
}
