/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:17:02 by vbastion          #+#    #+#             */
/*   Updated: 2017/12/13 18:44:49 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DLIST_H
# define FT_DLIST_H

# include "../../libft/inc/libft.h"

typedef struct s_dlist	t_dlist;

struct					s_dlist
{
	void				*content;
	t_dlist				*prev;
	t_dlist				*next;
};

void					ft_dlist_clear(t_dlist **list,
										void (*free_ptr)(void **));
t_dlist					*ft_dlist_create(void *content);
void					ft_dlist_free(t_dlist **elem,
										void (*free_ptr)(void **));
t_dlist					*ft_dlist_from_char(char c);
t_dlist					*ft_dlist_from_str(char *str);
t_dlist					*ft_dlist_insert(t_dlist *curr, t_dlist *chain);
t_dlist					*ft_dlist_last(t_dlist *list);
size_t					ft_dlist_len(t_dlist *head, t_dlist *end);
void					ft_dlist_repl(t_dlist *node, t_dlist *chain);
void					ft_dlist_repl_mult(t_dlist *beg, t_dlist *end,
											t_dlist *chain);
void					ft_dlist_swap(t_dlist *lhs, t_dlist *rhs);
char					*ft_dlist_to_str(t_dlist *begin, t_dlist *end);

t_dlist					*ft_dlist_findchar(t_dlist *lhs, char c);
void					ft_dlist_delone(t_dlist **to_del);

#endif
