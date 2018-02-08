/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terms_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 16:09:50 by vbastion          #+#    #+#             */
/*   Updated: 2017/11/27 13:46:14 by awyart           ###   ########.fr       */
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
