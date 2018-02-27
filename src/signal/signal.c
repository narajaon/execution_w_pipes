#include "header.h"

void		ft_doprompt(t_sh *sh)
{
	t_dlist_wrap *wrap;

	wrap = sh->wrap;
	ft_terms_toggle_key("cr");
	ft_terms_toggle_key("do");
	if (wrap != NULL)
	{
		wrap->pos = 0;
		wrap->size = 0;
		free_hlist(&wrap->head);
		wrap->head = NULL;
	}
	ft_prompt(sh);
}

void		ft_signal(int sig)
{
	if (g_test == 1)
		return ;
	if (sig == SIGWINCH)
	{
		ioctl(1, TIOCGWINSZ, &(g_sh->term.win));
		return ;
	}
	else if (sig == SIGTSTP)
	{
		ft_printf("Ne pas mettre de shell en fg, merci");
		ft_doprompt(g_sh);
	}
	else if (sig == SIGINT)
	{
		if (g_cur_pid > 0 && g_shlvl != g_lvl)
			kill(g_cur_pid, SIGQUIT);
		g_sh->ret = Q_OK;
		ft_doprompt(g_sh);
	}
	else
	{
		ft_printf("ERREUR : 21sh : <%d>", sig);
		ft_doprompt(g_sh);
	}
}

void		ft_signal2(int sig)
{
	if (sig == SIGINT)
		ft_printf("Vous avez cliqué sur Ctrl + C\n");
	else if (sig == SIGABRT)
		ft_printf("Abort\n");
	else if (sig == SIGSEGV)
		ft_printf("AHAHAHA c'est un segfault\n");
	else if (sig == SIGBUS)
		ft_printf("BUS ERROR\n");
	else if (sig == SIGFPE)
		ft_printf("Floating point exception\n");
	else
		ft_printf("ERREUR non identifiée par awsh <%d>\n", sig);
}

void		ft_getsignal(void)
{
	signal(SIGWINCH, &ft_signal);
	signal(SIGABRT, &ft_signal);
	signal(SIGINT, &ft_signal);
	signal(SIGBUS, &ft_signal);
	signal(SIGCONT, &ft_signal);
	signal(SIGTSTP, &ft_signal);
	signal(SIGKILL, &ft_signal);
	signal(SIGSTOP, &ft_signal);
}
