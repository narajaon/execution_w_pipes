/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:46:12 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/21 18:24:22 by narajaon         ###   ########.fr       */
/* ************************************************************************** */

#include "header.h"

void			flush_sh(t_sh *sh)
{
	free_hlist(&sh->list);
	free_hlist(&sh->hist->cur_branch);
	//free_autocmp_res(&sh->hist->branch_root);
	//free yanked list in list_wrap
}

void			ft_start_process(t_sh *sh)
{
	while (1)
	{
		sh->test = 1;
		ft_prompt(sh);
		ft_read(sh);
		ft_terms_toggle_key("cr");
		ft_terms_toggle_key("do");
		exec_cmd(sh->list);
		update_history(sh->hist, sh->list);
		flush_sh(sh);
	}
}

int				ft_init(t_sh *sh, t_hist *hist)
{
	sh->dir.dir_name = get_cur_dir(sh->dir.cur_dir);
	history_init(hist);
	g_cur_pid = 0;
	sh->hist = hist;
	sh->ret = Q_OK;
	setlocale(LC_ALL, "");
	ft_init_term();
	ft_terms_init(&(sh->term));
	ft_terms_toggle(&(sh->term), 1);
	ft_setupenv(&sh->env);
	get_sh_lvl(sh);
	return (1);
}

int				main(void)
{
	t_sh				sh;
	t_hist				hist;

	ft_bzero(&sh, sizeof(t_sh));
	g_sh = &sh;
	g_fd = open("/dev/ttys002", O_WRONLY);
	dprintf(g_fd, "\33[H\33[2J");
	if (!(ft_init(&sh, &hist)))
		return (0);
	ft_getsignal();
	tputs(tgetstr("cl", NULL), 1, &ft_putc);
	g_shlvl = g_lvl;
	dprintf(g_fd, "lvl <%d> sh_lvl<%d>\n", g_lvl, g_shlvl);
	ft_start_process(&sh);
	return (0);
}
