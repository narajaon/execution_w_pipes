/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:33:49 by narajaon          #+#    #+#             */
/*   Updated: 2017/11/19 12:44:41 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_params(t_env *e)
{
	e->cast.ll = 0;
	e->ucast.ll = 0;
	e->flags.width = 0;
	e->flags.precis = 0;
	e->flags.size = 0;
	e->flags.conv = 0;
	e->flags.opt.min = 0;
	e->flags.opt.hash = 0;
	e->flags.opt.sign = 0;
	e->flags.opt.decal = 0;
	e->flags.opt.fill_prec = '0';
	e->flags.opt.precis = 0;
	e->cast_size = 0;
	e->cast_id = 0;
	e->is_limit = 0;
	e->overflow = 0;
	e->cast_sign = 1;
}

int		ft_dprintf(int fd, char *str, ...)
{
	static t_env	e;

	e.cast_sign = 1;
	e.cur_fd = fd;
	e.flags.opt.fill_prec = '0';
	e.output_size = 0;
	e.flags.opt.star = 0;
	ft_bzero(e.out_tmp, sizeof(e.out_tmp));
	va_start(e.arg, str);
	fill_funtab(&e);
	print_str((char **)&str, &e);
	va_end(e.arg);
	return (e.output_size);
}

int		ft_printf(const char *str, ...)
{
	static t_env	e;

	e.cast_sign = 1;
	e.cur_fd = 1;
	e.flags.opt.fill_prec = '0';
	e.output_size = 0;
	e.flags.opt.star = 0;
	ft_bzero(e.out_tmp, sizeof(e.out_tmp));
	va_start(e.arg, str);
	fill_funtab(&e);
	print_str((char **)&str, &e);
	va_end(e.arg);
	return (e.output_size);
}
