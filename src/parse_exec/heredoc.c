#include "../../inc/header.h"

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
	return(str);
}

t_dlist 		*heredoc(char *str, t_sh *sh)
{
	t_dlist_wrap 	wrap;
	char 			*ref;
	char 			buf[3];
	
	ft_bzero(&wrap, sizeof(t_dlist_wrap));
	ioctl(1, TIOCGWINSZ, &(sh->term.win));
	wrap.col = sh->term.win.ws_col;
	ft_dprintf(STDERR_FILENO, "heredoc> ");
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
	if (ft_strncmp(ref, str, ft_strlen(str)))
	{
		ft_strdel(&ref);
		return (NULL);
	}
	ft_strdel(&ref);
	return (wrap.head);
}
