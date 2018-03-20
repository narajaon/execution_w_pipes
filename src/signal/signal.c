/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/20 15:13:39 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else if (sig == SIGINT)
	{
		if (g_cur_pid > 0 && g_shlvl != g_lvl)
			kill(g_cur_pid, SIGQUIT);
		g_sh->ret = Q_OK;
		if (g_lvl == 2)
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
		ft_printf("Vous avez cliqué sur Ctrl + C <%d>\n", g_cur_pid);
	else if (sig == SIGABRT)
		ft_printf("Abort pid <%d> \n", g_cur_pid);
	else if (sig == SIGSEGV)
		ft_printf("C'est un segfault de <%d>\n", g_cur_pid);
	else if (sig == SIGBUS)
		ft_printf("C'est un bus error de <%d>\n", g_cur_pid);
	else if (sig == SIGFPE)
		ft_printf("Floating point exception de <%d>\n", g_cur_pid);
	else if (sig == SIGPIPE)
		;
	else
		ft_printf("ERREUR non identifiée <%d>par mysh <%d>\n", g_cur_pid, sig);
}

void		ft_getsignal(void)
{
	signal(SIGWINCH, &ft_signal);
	signal(SIGABRT, &ft_signal);
	signal(SIGINT, &ft_signal);
	signal(SIGBUS, &ft_signal);
	signal(SIGCONT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGKILL, &ft_signal);
	signal(SIGSTOP, &ft_signal);
	signal(SIGSEGV, &ft_signal);
}
