/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:06:03 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/20 15:01:05 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_terms_init(t_terms *terms)
{
	tcgetattr(0, &(terms->prev_term));
	tcgetattr(0, &(terms->this_term));
	terms->this_term.c_lflag &= ~(ICANON | ECHO);
	terms->this_term.c_cc[VMIN] = 1;
	terms->this_term.c_cc[VTIME] = 0;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &(terms->win));
	terms->status = TERM_READY;
	tcsetattr(0, TCSANOW, &(terms->this_term));
	return (1);
}

int		ft_terms_toggle(t_terms *terms, int on)
{
	if (tcsetattr(0, TCSADRAIN, on ?
		&(terms->this_term) : &(terms->prev_term)) == -1)
		return (-1);
	return (1);
}

void	ft_terms_clear(t_terms **terms)
{
	free(*terms);
	*terms = NULL;
}

int		ft_putc(int c)
{
	return (write(0, &c, 1));
}

int		ft_terms_toggle_key(char *str)
{
	char				*tmp;

	if ((tmp = tgetstr(str, NULL)) == NULL)
		return (0);
	tputs(tmp, 1, &ft_putc);
	return (1);
}
