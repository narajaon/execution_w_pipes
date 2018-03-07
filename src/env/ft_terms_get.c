/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terms_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 16:09:50 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/07 17:39:59 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_terms				*ft_terms_get(void)
{
	static t_terms	terms = { .status = TERM_NULL };

	if (terms.status == TERM_NULL)
	{
		ft_bzero(&terms, sizeof(t_terms));
		terms.status = TERM_INIT;
		ft_terms_init(&terms);
	}
	return (&terms);
}
