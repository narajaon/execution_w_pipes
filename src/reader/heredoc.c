#include "header.h"

int		ft_quote(t_dlist_wrap *wrap, t_sh *sh)
{
	char buf[3];

	if (sh->ret == Q_OK)
		return (sh->ret);
	wrap->pos = wrap->size;
	ft_terms_toggle_key("cr");
	ft_terms_toggle_key("do");
	ft_prompt(sh);
	while (1)
	{
		ioctl(1, TIOCGWINSZ, &(sh->term.win));
		wrap->col = sh->term.win.ws_col;
		ft_bzero(buf, 3);
		read(STDIN_FILENO, buf,  3);
		if (apply_cap(buf, wrap, sh) == 0)
			break ;
	}
	if ((sh->ret = ft_handle_quote(wrap->head)) != Q_OK)
		sh->ret = ft_quote(wrap, sh);
	return (sh->ret);
}

static char 	check_quote(t_dlist *list)
{
	t_chr *schar;
	t_chr *prev;
	char last;

	schar = NULL;
	prev = NULL;
	last = '.';
	if (list != NULL)
		prev = list->content;
	while (list != NULL)
	{
		schar = list->content;
		if (prev && prev->c != '\\')
		{
			if (schar->c == '\"' && last == '\"')
				last = '.';
			else if (schar->c == '\'' && last == '\'')
				last = '.';
			else if (schar->c == '\"' && last == '.')
				last = '\"';
			else if (schar->c == '\'' && last == '.')
				last = '\'';
		}
		prev = schar;
		list = list->next;
	}
	return (last);
}

int		ft_handle_quote(t_dlist *list)
{
	char	last;
	t_chr	*schar;

	schar = NULL;
	last = check_quote(list);
	while (list != NULL && list->next != NULL)
		list = list->next;
	if (list != NULL)
		schar = list->content;
	if (last == '\'')
		return (QUOTE);
	if (last == '\"')
		return (DQUOTE);
	if (schar && schar->c == '|')
		return (Q_PIPE);
	if (schar && schar->c == '\\')
	{
		schar->c = '\n';
		return (SLASH);
	}
	return (Q_OK);
}
