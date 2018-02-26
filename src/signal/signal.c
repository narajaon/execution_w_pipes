/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:03:12 by awyart            #+#    #+#             */
/*   Updated: 2018/02/26 15:10:52 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void 	ft_doprompt(t_sh *sh)
{
	t_dlist_wrap *wrap;

	wrap = g_wrap;
	ft_terms_toggle_key("cr");
	ft_terms_toggle_key("do");
	free_hlist(&wrap->head);
	if (sh->hist->cur_branch != NULL)
	{
		hl_print_next(sh->hist->cur_branch, print_hlst_content);
		hl_print_next(sh->hist->branch_root, print_hlst_content);
		//sh->hist->cur_branch = sh->hist->branch_root;
	}
	if (wrap)
	{
		wrap->pos = 0;
		wrap->size = 0;
		wrap->head = NULL;
	}
	ft_prompt(sh);
}

void		ft_signal(int sig)
{
	if (g_lvl == g_shlvl)
	{
		if (sig == SIGWINCH)
		{
			ioctl(1, TIOCGWINSZ, &(g_sh->term.win));
			return ;
		}
		else if (sig == SIGTSTP)
		{
			ft_dprintf(STDERR_FILENO, "Ne pas mettre de shell en fg, merci\n");
			ft_doprompt(g_sh);
		}
		else if (sig == SIGINT)
		{
			ft_doprompt(g_sh);
		}
		else
		{
			ft_dprintf(STDERR_FILENO, "ERREUR : 21sh : <%d>\n", sig);
			ft_doprompt(g_sh);
		}
	}
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
