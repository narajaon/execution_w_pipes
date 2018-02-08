#include "../inc/levenshtein.h"

t_dlist			*compl_next(char *input, int in_size, t_dlist *root,
		t_dlist *to_cmp)
{
	t_dlist		*data;

	if (to_cmp != NULL)
		data = (to_cmp->next != NULL) ? to_cmp->next : to_cmp;
	else
		data = root;
	while (data)
	{
		if (ft_strncmp(input, data->content, in_size) == 0)
		{
			if (root != NULL)
				return (data);
			if (to_cmp && ft_strcmp(to_cmp->content, data->content) != 0)
				return (data);
		}
		data = data->next;
	}
	return (to_cmp);
}

t_dlist			*compl_prev(char *input, int in_size, t_dlist *root,
		t_dlist *to_cmp)
{
	t_dlist		*data;

	data = NULL;
	if (to_cmp != NULL)
		data = to_cmp->prev;
	while (data)
	{
		if (ft_strncmp(input, data->content, in_size) == 0)
		{
			if (root != NULL)
				return (data);
			if (to_cmp && ft_strcmp(to_cmp->content, data->content) != 0)
				return (data);
		}
		data = data->prev;
	}
	return (NULL);
}

const void		*g_compl_manip[2] = {&compl_prev, &compl_next};

int				input_to_buff(char *buff, t_dlist *input)
{
	t_chr		*content;
	int			i;

	i = 0;
	while (input)
	{
		content = input->content;
		buff[i++] = content->c;
		input = input->next;
	}
	buff[i] = '\0';
	return (i);
}

t_dlist			*completion_handler(int event, t_dlist *input, t_dlist *root,
		t_dlist *data)
{
	char			*term_buff;
	t_dlist			*(*compl_fun)(char *, int, t_dlist *, t_dlist *);
	t_dlist			*cur_branch;
	int				in_size;

	if (!(term_buff = (char *)malloc(sizeof(char) * hlst_size(input) + 1)))
		return (NULL);
	in_size = input_to_buff(term_buff, input);
	compl_fun = g_compl_manip[event];
	cur_branch = compl_fun(term_buff, in_size, root, data);
	free_str(&term_buff);
	return (cur_branch);
}

t_dlist			*completion_res(int event, t_dlist *input, t_hist *hstruct)
{
	static t_dlist		*result;

	if (event == 2)
		return (result = NULL);
	if (result == NULL)
		result = completion_handler(event, input, hstruct->history_root, NULL);
	else
		result = completion_handler(event, input, NULL, result);
	if (result == NULL)
	{
		free_hlist(&hstruct->cur_branch);
		hstruct->cur_branch = NULL;
		return (NULL);
	}
	free_hlist(&hstruct->cur_branch);
	hstruct->cur_branch = input_to_dlist(result->content);
	return (hstruct->cur_branch);
}
