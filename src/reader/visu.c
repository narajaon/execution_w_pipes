#include "header.h"

// int			ft_printlist(t_dlist_wrap *wrap, t_sh *sh, char buf[3])
// {
// 	t_dlist 	*list;
// 	t_chr		*schar;
// 	int 		i = 0;

// 	list = wrap->head;
// 	(void)sh;

// 	dprintf(g_fd, "\33[H\33[2JLIST \n");
// 	dprintf(g_fd, "pos  : %d\nsize : %d\n", wrap->pos, wrap->size);
// 	dprintf(g_fd, "col : %d\n", sh->term.win.ws_col);
// 	dprintf(g_fd, "<%d><%d><%d>\n", buf[0], buf[1], buf[2]);
// 	dprintf(g_fd, "offset : <%d>\n size +len:<%d>\nic<%d>\n", g_i1, g_i2, g_i2 % sh->term.win.ws_col);
// 	while (list != NULL)
// 	{
// 		schar = list->content;
// 		if (i != wrap->pos)
// 			dprintf(g_fd, "%c>", schar->c);
// 		else
// 			dprintf(g_fd, "\033[0;7;37;40m %c \033[0;0;0;0m->", schar->c);
// 		list = list->next;
// 		i++;
// 	}
// 	dprintf(g_fd,"NULL\n");
// 	if (wrap)
// 	{
// 		if (wrap->head)
// 		{
// 			schar = wrap->head->content;
// 			dprintf(g_fd, " head <%c>", schar->c);
// 		}
// 	}
// 	return (0);
// }
