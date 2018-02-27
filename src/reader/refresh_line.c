#include "header.h"

static void	nextline(void)
{
	ft_terms_toggle_key("cr");
	ft_terms_toggle_key("do");
}

int			reset_cursor(t_dlist_wrap *wrap, t_sh *sh)
{
	int offset;
	int i;
	int col;

	offset = wrap->size - wrap->pos + 1;
	i = wrap->size + len_prompt(sh);
	col = sh->term.win.ws_col;
	if ((wrap->size + len_prompt(sh)) % col == 0)
		nextline();
	while (--offset > 0)
	{
		col = sh->term.win.ws_col;
		if (i % sh->term.win.ws_col == 0)
		{
			ft_terms_toggle_key("cr");
			ft_terms_toggle_key("up");
			while (--col)
				ft_terms_toggle_key("nd");
		}
		else
			ft_terms_toggle_key("le");
		i--;
	}
	return (wrap->size - wrap->pos);
}

int			ft_print_list(t_dlist_wrap *wrap, t_sh *sh)
{
	t_chr	*schar;
	t_dlist	*list;

	ft_prompt(sh);
	if (sh->ret == Q_OK || wrap->tmp == NULL)
		list = wrap->head;
	else
		list = wrap->tmp->next;
	while (list != NULL)
	{
		schar = list->content;
		write(STDOUT_FILENO, &schar->c, 1);
		list = list->next;
	}
	return (0);
}

int			count_tmp(t_dlist_wrap *wrap, int pos)
{
	int i;
	int size;

	size = ft_count_string(wrap->head);
	i = ft_count_string(wrap->tmp);
	return (pos - (size - i));
}

int			refresh_line(t_dlist_wrap *wrap, t_sh *sh)
{
	int			i;
	int			col;
	static int	pos = 0;

	if (sh->test == 1)
		pos = 0;
	if (sh->hist_multi != 0)
		pos = sh->hist_multi;
	col = wrap->col;
	if (sh->ret == Q_OK)
		i = (pos + len_prompt(sh)) / (col) + 1;
	else
		i = (count_tmp(wrap, pos) + len_prompt(sh)) / (col) + 1;
	while (--i)
	{
		if (i <= 0)
			break ;
		ft_terms_toggle_key("cr");
		ft_terms_toggle_key("cd");
		ft_terms_toggle_key("al");
		ft_terms_toggle_key("up");
	}
	ft_terms_toggle_key("cr");
	ft_terms_toggle_key("cd");
	ft_terms_toggle_key("al");
	ft_print_list(wrap, sh);
	pos = wrap->pos;
	sh->hist_multi = 0;
	return (1);
}
