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

#include "../inc/header.h"


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
		ft_prompt(sh);
		ft_read(sh);
		write(STDOUT_FILENO, "\n", 1);
		dprintf(g_fd, "\n --<Read OK>---\n ");
		exec_cmd(sh->list);
		dprintf(g_fd, "\n --<Exec OK>---\n ");
		update_history(sh->hist, sh->list);
		flush_sh(sh);
	}
}

int				ft_init(t_sh *sh)
{
	sh->dir.dir_name = get_cur_dir(sh->dir.cur_dir);
	ft_init_term();
	ft_terms_init(&sh->term);
	ft_terms_toggle(&sh->term, 1);
	ft_setupenv(&sh->env);
	return (1);
}

int				main(void)
{
	t_sh				sh;
	t_hist				hist;

	//g_cur_pid = getpid();
	g_shlvl = 0;
	g_cur_pid = 0;
	g_sh = &sh;
	g_fd = open("/dev/ttys001", O_WRONLY);
	history_init(&hist);
	sh.hist = &hist;
	sh.ret = Q_OK;
	setlocale(LC_ALL, "");
	if (!(ft_init(&sh)))
		return (0);
	ft_getsignal();
	//tputs(tgetstr("cl", NULL), 1, &ft_putc);
//	tputs(tgetstr("cl", NULL), 1, &ft_putc);
//	sig_intercepter();
	ft_start_process(&sh);
	return (0);
}
