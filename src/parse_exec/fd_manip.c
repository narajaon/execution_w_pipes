#include "../../inc/header.h"

const t_red		g_redir[R_NB + 1] =
{
	{"<", R_LEFT, &redir_left},
	{">", R_RIGHT, &redir_right},
	{"<<", R_DLEFT, &redir_dleft},
	{">>", R_DRIGHT, &redir_dright},
	{NULL, -1, NULL}
};

void			close_fd(int *pfd)
{
	close(pfd[0]);
	close(pfd[1]);
}

int				get_redir(char *av, void (**redir)())
{
	int			i;

	i = 0;
	while (g_redir[i].redir != NULL)
	{
		if (ft_strncmp(g_redir[i].redir, av, 2) == 0)
			break ;
		i++;
	}
	*redir = g_redir[i].funct;
	return (i);
}

void			redir_left(char **av)
{
	(void)av;
}

void			redir_right(char **av)
{
	(void)av;
}

void			redir_dleft(char **av)
{
	(void)av;
}

void			redir_dright(char **av)
{
	(void)av;
}

char			**parse_redir(char *input)
{
	char		**parsed;
	char		**av;
	void		(*redir)(char **);
	int			i;

	i = 0;
	av = ft_strsplit(input, ' ');
	parsed = (char **)malloc(sizeof(char *) * (ft_tablen(av) + 1));
	while (av[i] != NULL)
	{
		i += get_redir(av[i], &redir);
	}
	free_tab_str(&av);
	parsed[i] = NULL;
	return (parsed);
}
