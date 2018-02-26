/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:46:12 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/26 14:14:00 by narajaon         ###   ########.fr       */
/* ************************************************************************** */

#include "../inc/header.h"

void			flush_sh(t_sh *sh)
{
	free_hlist(&sh->list);
	free_hlist(&sh->hist->cur_branch);
	//free yanked list in list_wrap
}

void			ft_start_process(t_sh *sh)
{
	while (1)
	{
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
	g_lvl = 2;
	history_init(hist);
	sh->hist = hist;
	sh->ret = Q_OK;
	setlocale(LC_ALL, "");
	ft_init_term();
	ft_terms_init(&(sh->term));
	ft_terms_toggle(&(sh->term), 1);
	ft_setupenv(&sh->env);
	sh->stdio[0] = dup(STDIN_FILENO);
	sh->stdio[1] = dup(STDOUT_FILENO);
	sh->stdio[2] = dup(STDERR_FILENO);
	return (1);
}

int				main(void)
{
	t_sh				sh;
	t_hist				hist;

	g_sh = &sh;
	g_fd = open("/dev/ttys001", O_WRONLY);
	if (!(ft_init(&sh, &hist)))
		return (0);
	ft_getsignal();
	//tputs(tgetstr("cl", NULL), 1, &ft_putc);
	g_shlvl = g_lvl;
	ft_start_process(&sh);
	return (0);
}
