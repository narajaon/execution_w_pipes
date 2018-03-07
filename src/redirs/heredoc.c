#include "header.h"

static char		*list_to_str(t_dlist *list)
{
	int count;
	char *str;
	t_chr *schar;

	count = ft_count_string(list);
	if (!(str = (char *)malloc(count + 1)))
		return (NULL);
	count = 0;
	while (list != NULL)
	{
		schar = list->content;
		str[count++] = schar->c;
		list = list->next;
	}
	str[count] = '\0';
	return (str);
}

char 		*heredoc(t_sh *sh)
{
	t_dlist_wrap 	wrap;
	char 			*ref;
	char 			buf[3];

	g_sh->ret = Q_HEREDOC;
	ft_bzero(&wrap, sizeof(t_dlist_wrap));
	ioctl(1, TIOCGWINSZ, &(sh->term.win));
	wrap.col = sh->term.win.ws_col;
	ft_prompt(sh);
	while (1)
	{
		ioctl(1, TIOCGWINSZ, &(sh->term.win));
		wrap.col = sh->term.win.ws_col;
		ft_bzero(buf, 3);
		read(STDIN_FILENO, buf,  3);
		if (apply_cap(buf, &wrap, sh) == 0)
			break ;
	}
	ref = list_to_str(wrap.head);
	ft_terms_toggle_key("cr");
	ft_terms_toggle_key("do");
	return (ref);
}

char 	*handle_heredoc(char *str, t_sh *sh)
{
	char *ref;
	char *line;
	char *line2;
	int i;

	g_test = 1;
	ref = NULL;
	line = ft_strdup("\0");
	while (1)
	{
		ref = heredoc(sh);
		if (ref != NULL)
		{
			if ((i = ft_strcmp(ref, str)) == 0)
				break ;
			line2 = ft_strjoin_spe(line, ref, '\n');
			ft_strdel(&line);
			ft_strdel(&ref);
			line = line2;
			line2 = NULL;
		}
	}
	g_sh->ret = Q_OK;
	g_test = 0;
	ft_strdel(&ref);
	return (line);
}
