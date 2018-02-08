#include "../../inc/header.h"

void		hl_print_str(t_dlist *list)
{
	if (list == NULL)
		return ;
	printf("##%s\n##", list->content);
}

char		*split_by_token(t_dlist **procs, char *input, char token)
{
	int			i;
	char		*sub;

	i = 0;
	//need to check if between quotes
	while (input[i] && input[i] != token)
		i++;
	sub = ft_strsub(input, 0, i);
	ft_hlstadd_back_void(procs, sub);
	if (input[i] != '\0')
		return (&input[i + 1]);
	return (&input[i]);
}

t_dlist		*init_proc_list(char *input, char token)
{
	t_dlist		*procs;

	procs = NULL;
	while (*input != '\0')
		input = split_by_token(&procs, input, token);
	return (procs);
}
