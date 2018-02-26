#include "header.h"

static void		printlist(t_dlist *list)
{
	t_chr	*schar;

	while (list != NULL)
	{
		schar = list->content;
		ft_printf("%s%c%s", KGRN, schar->c, KNRM);
		list = list->next;
	}
}

static int		move_down(t_dlist_wrap *wrap, t_sh *sh, int mode)
{
	t_dlist		*begin;
	t_dlist		*list;
	int			var;
	int			i;

	begin = wrap->head;
	list = completion_res(IR_DOWN, begin, sh->hist);
	var = ((mode == 0) ? wrap->pos : ft_count_string(sh->hist->last));
	if (var == 0)
		var = wrap->pos; 
	i = (var + len_prompt(sh)) / sh->term.win.ws_col + 1;
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
	ft_prompt(sh);
	printlist((list == NULL) ? wrap->head : list);
	return (1);
}

static int		move_up(t_dlist_wrap *wrap, t_sh *sh, int mode)
{
	t_dlist		*begin;
	t_dlist		*list;
	int			var;
	int			i;

	begin = wrap->head;
	list = completion_res(IR_UP, begin, sh->hist);
	var = ((mode == 0) ? wrap->pos : ft_count_string(sh->hist->last));
	if (var == 0)
		var = wrap->pos; 
	i = (var + len_prompt(sh)) / sh->term.win.ws_col + 1;
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
	ft_prompt(sh);
	printlist((list == NULL) ? wrap->head : list);
	return (1);
}

static void		modif_hist(t_dlist_wrap *wrap, t_sh *sh)
{
	t_dlist *todel;

	todel = wrap->head;
	wrap->head = sh->hist->cur_branch;
	wrap->pos = ft_count_string(wrap->head);
	wrap->size = ft_count_string(wrap->head);
	wrap->tmp = NULL;
	free_hlist(&todel);
}

int				move_updown(t_dlist_wrap *wrap, char buf[3], t_sh *sh)
{
	if (sh->ret == Q_HEREDOC)
		return (0);
	if (buf[2] == 65)
		move_up(wrap, sh, 0);
	else if (buf[2] == 66)
		move_down(wrap, sh, 0);
	while (1)
	{
		read(STDIN_FILENO, buf, 3);
		if (!(is_updown(buf)))
			break ;
		if (buf[2] == 65)
			move_up(wrap, sh, 1);
		else if (buf[2] == 66)
			move_down(wrap, sh, 1);
	}
	if (sh->hist->cur_branch != NULL)
		modif_hist(wrap, sh);
	sh->hist_multi = ft_count_string(sh->hist->cur_branch);
	sh->hist->cur_branch = NULL;
	completion_res(2, NULL, NULL);
	return (apply_cap(buf, wrap, sh));
}
