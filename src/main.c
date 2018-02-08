/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:46:12 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/05 13:35:08 by narajaon         ###   ########.fr       */
/* ************************************************************************** */

#include "header.h"

t_sh			*g_sh;

void			ft_start_process(t_sh *sh)
{
	g_sh = sh;
	while (1)
	{
		ft_prompt(sh);
		dprintf(g_fd, "\n --<Prompt OK>---\n ");
		ft_read(sh);
		write(STDOUT_FILENO, "\n", 1);
		dprintf(g_fd, "\n --<Read OK>---\n ");
		ft_lexer(sh);
		dprintf(g_fd, "\n --<Lexer OK>---\n ");
		//here
		if (ft_parser(sh) == 0)
		 {
		 	ft_printf("\n");
		 	continue;
		}
		dprintf(g_fd, "\n --<Parser ok>---\n ");
		//ft_extension();
//		ft_execution(sh);
		exec_cmd(sh->list);
		//exec_cmd(sh
		dprintf(g_fd, "\n --<Exec ok>---\n ");
		update_history(sh->hist, sh->list);
		//free needed sh
	}
}

int				ft_init(t_sh *sh)
{
	g_sh = sh;
	sh->dir.dir_name = get_cur_dir(sh->dir.cur_dir);
	ft_init_term();
	ft_terms_init(&sh->term);
	ft_terms_toggle(&sh->term, 1);
	ft_init_keytab();
	ft_setupenv(&sh->env);
	return (1);
}

void			flush_sh(t_sh *sh)
{
	free_hlist(&sh->list);
	free_hlist(&sh->hist->cur_branch);
	free_autocmp_res(&sh->hist->branch_root);
	//free btree
	//free process
	//free token
	//free yanked list in list_wrap
}

int				main(void)
{
	t_sh				sh;
	t_hist				hist;

	g_fd = open("/dev/ttys001", O_WRONLY);
	history_init(&hist);
	sh.hist = &hist;
	sh.ret = Q_OK;
	setlocale(LC_ALL, "");
	if (!(ft_init(&sh)))
		return (0);
	g_loop = TRUE;
	ft_getsignal();
//	tputs(tgetstr("cl", NULL), 1, &ft_putc);
//	sig_intercepter();
	ft_start_process(&sh);
	//free(&sh);
	return (0);
}
