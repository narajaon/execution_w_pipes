#include "../../inc/header.h"

void		write_next(pid_t *reading, pid_t *writting)
{
	dup2(*reading, STDOUT_FILENO);
	(void)reading;
	close(*reading);
	(void)writting;
}

void		read_prev(pid_t *reading, pid_t *writting)
{
	dup2(*writting, STDIN_FILENO);
	(void)reading;
	close(*reading);
	(void)writting;
}

void		close_fd(int *pfd)
{
	close(pfd[0]);
	close(pfd[1]);
}

//>
int 		simple_redir(int fd, char *file)
{
	int tmp;
	char buf[128];
	int ret;

	//fd est le file descriptor contenant la sortie du process
	ft_bzero(buf, 128);
	if (!(tmp = open(file, O_CREAT | S_IRWXO)))
		return (0);
	while ((ret = read(fd, buf, 128)) > 0)
	{
		write(tmp, buf, ret);
	}
	close (tmp);
	return (1);
	// rajouter une condition si c'est la derniere redirection de la serie pour fermer STDOUT
}

//>>
int 		double_redir(int fd, char *file)
{
	int tmp;
	char buf[128];
	int ret;

	//fd est le file descriptor contenant la sortie du process
	ft_bzero(buf, 128);
	if (!(tmp = open(file, O_CREAT | S_IRWXO | O_APPEND)))
		return (0);
	while ((ret = read(fd, buf, 128)) > 0)
	{
		write(tmp, buf, ret);
	}
	close (tmp);
	return (1);
	// rajouter une condition si c'est la derniere redirection de la serie pour fermer STDOUT
}

// <
int 		input_redir(int fd, char *file)
{
	int tmp;
	char buf[128];
	int ret;

	//fd est le file descriptor contenant l'entrée du process
	ft_bzero(buf, 128);
	if (!(tmp = open(file, O_CREAT | S_IRWXO | O_APPEND)))
		return (0);
	while ((ret = read(tmp, buf, 128)) > 0)
	{
		write(fd, buf, ret);
	}
	close (tmp);
	return (1);
	// rajouter une condition si c'est la derniere redirection de la serie pour fermer STDOUT
}

static char *list_to_str(t_dlist *list)
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
