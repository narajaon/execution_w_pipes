#include "header.h"

static int	init_cap_esc(char b, char c, int i, int (*f)())
{
	if (f == NULL)
		return (0);
	g_handleinput[i].cap[0] = 27;
	g_handleinput[i].cap[1] = b;
	g_handleinput[i].cap[2] = c;
	g_handleinput[i].f = f;
	return (1);
}

static int	init_cap_del(char a, char b, int i, int (*f)())
{
	if (f == NULL)
		return (0);
	g_handleinput[i].cap[0] = a;
	g_handleinput[i].cap[1] = b;
	g_handleinput[i].cap[2] = 0;
	g_handleinput[i].f = f;
	return (1);
}

static int	init_cap_shift(char a, char b, int i, int (*f)())
{
	if (f == NULL)
		return (0);
	g_handleinput[i].cap[0] = 59;
	g_handleinput[i].cap[1] = a;
	g_handleinput[i].cap[2] = b;
	g_handleinput[i].f = f;
	return (1);
}

static void	init_tab(void)
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
}

int			init_cap(void)
{
	init_tab();
	init_cap_esc(91, 65, K_UP, &move_updown);
	init_cap_esc(91, 66, K_DOWN, &move_updown);
	init_cap_esc(91, 67, K_RIGHT, &move_right);
	init_cap_esc(91, 68, K_LEFT, &move_left);
	init_cap_esc(91, 70, K_END, &move_end);
	init_cap_esc(91, 72, K_HOME, &move_home);
	init_cap_shift(50, 65, K_PUP, &move_sup);
	init_cap_shift(50, 66, K_PDOWN, &move_sdown);
	init_cap_shift(50, 67, K_PRIGHT, &move_sright);
	init_cap_shift(50, 68, K_PLEFT, &move_sleft);
	init_cap_del(127, 0, K_DEL, &handle_del);
	init_cap_del(126, 0, K_DELR, &handle_del_right);
	init_cap_del(28, 0, K_QUIT, &ft_quit);
	init_cap_del(4, 0, K_CTRLD, &ft_quit);
	init_cap_del(11, 0, K_CUT, &cut_list);
	init_cap_del(12, 0, K_YANK, &paste_list);
	init_cap_del(9, 0, K_TAB, &printlvl);
	return (0);
}
