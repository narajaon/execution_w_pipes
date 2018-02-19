#include "header.h"

int ft_quit()
{
	exit(0);
}

int init_cap_esc(char b, char c, int i, int (*f)())
{
	if (f == NULL)
		return (0);
	g_handleinput[i].cap[0] = 27;
	g_handleinput[i].cap[1] = b;
	g_handleinput[i].cap[2] = c;
	g_handleinput[i].f = f;
	return (1);
}

int init_cap_del(char a, char b, int i, int (*f)())
{
	if (f == NULL)
		return (0);
	g_handleinput[i].cap[0] = a;
	g_handleinput[i].cap[1] = b;
	g_handleinput[i].cap[2] = 0;
	g_handleinput[i].f = f;
	return (1);
}

int init_cap_shift(char a, char b, int i, int (*f)())
{
	if (f == NULL)
		return (0);
	g_handleinput[i].cap[0] = 59;
	g_handleinput[i].cap[1] = a;
	g_handleinput[i].cap[2] = b;
	g_handleinput[i].f = f;
	return (1);
}

int 	init_cap(void)
{
	int i;

	i = -1;
	while (++i < CAP_SIZE)
	{
		g_handleinput[i].f = NULL;
		g_handleinput[i].cap[0] = 0;
		g_handleinput[i].cap[1] = 0;
		g_handleinput[i].cap[2] = 0;
	}
	//init_cap_esc(91, 65, K_UP, &move_updown);
	//init_cap_esc(91, 66, K_DOWN, &move_updown);
	init_cap_esc(91, 67, K_RIGHT, &move_right);
	init_cap_esc(91, 68, K_LEFT, &move_left);
	init_cap_esc(91, 70, K_END, &move_end);
	init_cap_esc(91, 72, K_HOME, &move_home);
	init_cap_shift(50, 65, K_PUP, &move_sup);
	init_cap_shift(50 ,66, K_PDOWN, &move_sdown);
	init_cap_del(127, 0, K_DEL, &handle_del);
	init_cap_del(126, 0, K_DELR, &handle_del_right);
	//./init_cap_del(28, 0, K_QUIT, &ft_quit);
	// init_cap_del(, 0, K_SIGINT, &ctrlc);
	// init_cap_del(, 0, K_CTRLD, &ctrlD);
	// init_cap_del(11, 0, K_CUT, &cut_list);
	// init_cap_del(12, 0, K_YANK, &paste_list);
	return (0);
}


int			get_func(char buf[3])
{
	int i;
	int k;

	i = -1;
	k = 2;
	if (is_printable(buf))
		return (-1);
	while (++i < CAP_SIZE)
	{
		if (ft_strncmp(buf, g_handleinput[i].cap, 3) == 0)
			return (i);
	}
	return (-2);
}

int 	apply_cap(char buf[3], t_dlist_wrap *wrap, t_sh *sh)
{
	int ret = 0;
	int (*ptr)() = NULL;

	if (is_break(buf))
	{
		refresh_line(wrap, sh);
		return (0);
	}
	ret = get_func(buf);
	if (ret >= 0)
	{
		ptr = g_handleinput[ret].f;
		ret = ptr(wrap, buf, sh);
	}
	else if (ret == -1)
	 	handle_char(buf, wrap);
	refresh_line(wrap, sh);
	reset_cursor(wrap, sh);
	return (1);
}

int			ft_read(t_sh *sh)
{
	char			buf[3];
	t_dlist_wrap	wrap;

	ft_bzero(&wrap, sizeof(t_dlist_wrap));
	init_cap();
	while (1)
	{
		ioctl(1, TIOCGWINSZ, &(sh->term.win));
		wrap.col = sh->term.win.ws_col;
		ft_bzero(buf, 3);
		read(STDIN_FILENO, buf,  3);
		if (apply_cap(buf, &wrap, sh) == 0)
			break ;
	}
	sh->ret = ft_handle_quote(wrap.head);
	if (sh->ret != Q_OK)
		ft_quote(&wrap, sh);
	sh->list = wrap.head;
	return (1);
}
