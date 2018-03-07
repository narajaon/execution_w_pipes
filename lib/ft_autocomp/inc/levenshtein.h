/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levenshtein.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:34:54 by awyart            #+#    #+#             */
/*   Updated: 2018/03/07 17:46:21 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEVENSHTEIN_H
# define LEVENSHTEIN_H

# include "../../ft_printf/inc/ft_printf.h"
# include "../../libft/inc/libft.h"
# include "../../ft_dlist/inc/ft_dlist.h"
# include "macros.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <termcap.h>
# include <termios.h>

# define CMD_SIZE 10

typedef enum			e_ir
{
	IR_DOWN,
	IR_UP,
	IR_LEFT,
	IR_RIGHT,
	IR_RESET,
	IR_SIZE
}						t_ir;

typedef struct			s_chr
{
	char				c;
	char				is_escaped;
}						t_chr;

typedef struct			s_hist
{
	t_dlist				*cur_branch;
	t_dlist				*last;
	t_dlist				*branch_root;
	t_dlist				*history_root;
	char				hist_path[PATH_MAX + 1];
	int					history_fd;
}						t_hist;

typedef struct			s_lev
{
	char				content;
	t_dlist				*child;
}						t_lev;

void					*g_compl_manip[IR_SIZE];

int						input_to_buff(char *buff, t_dlist *input);
int						hlst_size(t_dlist *list);
void					free_str(char **str);
void					free_hlist(t_dlist **list);
void					free_hlist_not_content(t_dlist **list);

t_dlist					*compl_next(char *input, int in_size, t_dlist *root,
		t_dlist *to_cmp);
t_dlist					*compl_prev(char *input, int in_size, t_dlist *root,
		t_dlist *to_cmp);
t_dlist					*substr_next(char *input, int in_size, t_dlist *root,
		t_dlist *to_cmp);
t_dlist					*substr_prev(char *input, int in_size, t_dlist *root,
		t_dlist *to_cmp);

t_dlist					*history_up(t_dlist *word, t_dlist *cur_branch,
		t_dlist *history);
t_dlist					*history_down(t_dlist *word, t_dlist *cur_branch,
		t_dlist *history);
t_dlist					*get_branch(t_dlist *input, t_dlist *data_base);
t_dlist					*get_next_child(t_dlist *input, t_dlist *data_base);

t_lev					*new_lev_node(t_dlist *c);
t_lev					*new_lev_node_c(char *c);
t_lev					*lev_dup(t_lev *lev);
t_dlist					*ft_hlstnew(t_lev *nu);
t_dlist					*ft_hlstnew_void(void *nu);
t_dlist					*new_hlist_dlist(t_dlist *list);

t_dlist					*add_to_tree_end(t_dlist **tree, t_lev *nu);
void					add_to_child(t_dlist **child, t_dlist *word);
void					add_dlist_to_child(t_dlist **parent, t_dlist *child);
void					add_branch_to_input(t_dlist **input, t_dlist *branch);
void					check_child_list(t_dlist **child, t_dlist *word);
void					list_to_lev_tree(t_dlist **tree_nodes,
		t_dlist *data_base);

void					print_chr(t_dlist *lst);
void					print_child(t_dlist *child);
void					print_history(t_dlist *input, t_dlist *branch);
void					print_hlst_content(t_dlist *list);
void					print_branch(t_dlist *branch);

void					hlst_free(t_dlist **list);

void					remove_zero(t_dlist **dlist);
t_dlist					*hlget_last(t_dlist *list);
t_dlist					*hl_node_dup(t_dlist *node, size_t size);
t_dlist					*hlist_cpy(t_dlist *tree);
t_dlist					*hlist_cpy_minus(t_dlist *tree);
void					ft_hlstadd(t_dlist **alst, t_dlist *nu);
void					ft_hlstadd_void(t_dlist **alst, void *nu);
void					ft_hlstadd_back(t_dlist **alst, t_dlist *nu);
void					ft_hlstadd_back_void(t_dlist **alst, void *nu);
void					hl_print_next(t_dlist *list, void (*print)());
t_dlist					*ft_dlist_dup(t_dlist *src, size_t size);

char					*read_input(void);
void					add_to_history(char *str, int *fd);
void					update_history(t_hist *hist, t_dlist *new_cmd);
t_dlist					*history_to_tree(int fd);
t_dlist					*str_to_dlist(char *input);
void					tree_to_list(t_dlist *prev, t_dlist *cur,
		t_dlist **list);
t_dlist					*input_to_dlist(char *input);
t_dlist					*hl_list_dup(t_dlist *node);
#endif
