/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 11:39:44 by narajaon          #+#    #+#             */
/*   Updated: 2018/02/21 09:54:08 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

# define EMJ_ARRW 0x27A1

# define STR(x)		ft_printf(#x " = !%s!\n", x)
# define NBR(x)		ft_printf(#x " = !%d!\n", x)
# define CHAR(x)	ft_printf(#x " = !%c!\n", x)
# define EX			exit(1);
# define ICI		ft_printf("ICI\n");
# define LA			ft_printf("LA\n");
# define SEP		ft_printf("\n-----------------------------------------\n");

# define HISTORY ".mysh_history"
# define STDI 0
# define STDO 1
# define STDE 2

# define CMD_SIZE 10
#endif
