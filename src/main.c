/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:38:28 by awyart            #+#    #+#             */
/*   Updated: 2018/03/20 17:22:20 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void			flush_sh(t_sh *sh)
{
	free_hlist(&sh->list);
	free_hlist(&sh->hist->cur_branch);
	free(sh->wrap);
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
	free_hlist(&sh->yanked);
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
	init_cap();
	get_sh_lvl(sh);
	return (1);
}

int				main(int ac, char **av, char **environ)
{
	t_sh				sh;
	t_hist				hist;

	g_environ = environ;
	ft_bzero(&sh, sizeof(t_sh));
	if (ac >= 2)
	{
		if (ft_strcmp(av[1], "-g") == 0)
			sh.color = 1;
		else
			return (0);
	}
	g_sh = &sh;
	if (!(ft_init(&sh, &hist)))
		return (0);
	ft_getsignal();
	g_shlvl = g_lvl;
	ft_start_process(&sh);
	return (0);
}
