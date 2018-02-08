#ifndef AUTOCOMPLETION_H
# define AUTOCOMPLETION_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <termcap.h>
# include <termios.h>

# include "levenshtein.h"

void		history_init(t_hist *hstruct);
t_dlist		*history_handler(int event, t_dlist *input, t_hist *hstruct);
void		free_lev_tree(t_dlist **tree);
void		free_autocmp_res(t_dlist **data_base);

t_dlist		*completion_res(int event, t_dlist *input, t_hist *hstruct);
t_dlist		*history_to_list(int fd);
#endif
