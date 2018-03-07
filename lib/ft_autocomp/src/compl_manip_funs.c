#include "../inc/levenshtein.h"

void			*g_compl_manip[IR_SIZE] =
{
	&compl_prev, &compl_next, &substr_prev, &substr_next
};

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

t_dlist			*substr_next(char *input, int in_size, t_dlist *root,
		t_dlist *to_cmp)
{
	t_dlist		*data;

	(void)in_size;
	if (to_cmp != NULL)
		data = (to_cmp->next != NULL) ? to_cmp->next : to_cmp;
	else
		data = root;
	while (data)
	{
		if (ft_strstr(data->content, input) == 0)
		{
			if (root != NULL)
				return (data);
			if (to_cmp && ft_strcmp(to_cmp->content, data->content) == 0)
				return (data);
		}
		data = data->next;
	}
	return (to_cmp);
}

t_dlist			*substr_prev(char *input, int in_size, t_dlist *root,
		t_dlist *to_cmp)
{
	t_dlist		*data;

	(void)in_size;
	data = NULL;
	if (to_cmp != NULL)
		data = to_cmp->prev;
	while (data)
	{
		if (ft_strstr(data->content, input) == 0)
		{
			if (root != NULL)
				return (data);
			if (to_cmp && ft_strcmp(to_cmp->content, data->content) == 0)
				return (data);
		}
		data = data->prev;
	}
	return (NULL);
}
