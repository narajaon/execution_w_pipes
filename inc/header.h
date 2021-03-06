/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awyart <awyart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:30:43 by awyart            #+#    #+#             */
/*   Updated: 2018/03/20 18:16:02 by awyart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <term.h>
# include <signal.h>
# include <curses.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../lib/libft/inc/libft.h"
# include "../lib/ft_printf/inc/ft_printf.h"
# include "../lib/ft_dlist/inc/ft_dlist.h"
# include "../lib/ft_autocomp/inc/autocompletion.h"

# define HEREFILE "/tmp/.myherefile"
# define ERR_MALLOC "erreur dans l'attribution de memoire malloc \n"
# define MAX_FD		9
# define SCHAR_NB	8

typedef struct termios	t_termios;
typedef struct winsize	t_win;
typedef int				(*t_intfunc)();

enum	e_term_status
{
	TERM_NULL,
	TERM_INIT,
	TERM_READY
};

enum	e_quote_status
{
	Q_OK,
	QUOTE,
	DQUOTE,
	SLASH,
	Q_PIPE,
	Q_HEREDOC,
	QUOT_SIZE
};

enum	e_built
{
	B_ECHO,
	B_CD,
	B_ENV,
	B_SETENV,
	B_UNSETENV,
	B_EXIT,
	B_HASH,
	B_COLOR,
	BUILD_IN_SIZE
};

enum	e_cap
{
	K_UP,
	K_DOWN,
	K_RIGHT,
	K_LEFT,
	K_END,
	K_HOME,
	K_PUP,
	K_PDOWN,
	K_PRIGHT,
	K_PLEFT,
	K_DEL,
	K_DELR,
	K_CTRLD,
	K_CUT,
	K_YANK,
	K_TAB,
	K_QUIT,
	CAP_SIZE
};

enum					e_redir
{
	R_LEFT,
	R_RIGHT,
	R_DLEFT,
	R_DRIGHT,
	R_NB
};

typedef struct			s_schar
{
	char				sequ[3];
	char				asc;
}						t_schar;

typedef struct			s_red
{
	char				*redir;
	int					index;
	int					(*funct)();
}						t_red;

typedef struct			s_terms
{
	t_termios			prev_term;
	t_termios			this_term;
	int					status;
	int					current;
	t_win				win;
}						t_terms;

typedef struct			s_environ
{
	char				**env;
	int					size;
}						t_environ;

typedef struct			s_dlist_wrap
{
	t_dlist				*head;
	t_dlist				*tmp;
	t_dlist				*yanked;
	int					pos;
	int					size;
	int					col;
}						t_dlist_wrap;

typedef struct			s_cap
{
	char				cap[8];
	int					(*f)();
}						t_cap;

typedef struct			s_dir
{
	char				cur_dir[PATH_MAX + 1];
	char				prev_dir[PATH_MAX + 1];
	char				*dir_name;
}						t_dir;

typedef struct			s_proc
{
	t_dlist				*semicol;
	t_dlist				*pipes;
}						t_proc;

typedef struct			s_hash
{
	char				*cmd;
	char				*path;
}						t_hash;

typedef struct			s_sh
{
	t_environ			env;
	t_terms				term;
	t_dir				dir;
	t_dlist_wrap		*wrap;
	t_dlist				*list;
	t_dlist				*yanked;
	t_hist				*hist;
	t_dlist				*hash;
	int					stdio[3];
	int					ret;
	int					test;
	int					hist_multi;
	int					color;
}						t_sh;

typedef struct			s_op
{
	char				*name;
	int					(*fun_ptr)(t_sh *, char **);
}						t_op;

int						g_shlvl;
int						g_lvl;
t_sh					*g_sh;
int						g_cur_pid;
int						g_test;
char					**g_environ;
void					*g_handlenonchar[SCHAR_MAX];
t_schar					g_spec_char[SCHAR_NB];
t_cap					g_handleinput[CAP_SIZE + 1];
t_op					g_built_in[BUILD_IN_SIZE + 1];

void					ft_init_keytab(void);
int						init_cap(void);
int						get_sh_lvl(t_sh *sh);
int						ft_cd(t_sh *sh, char **av);
char					*get_cur_dir(char *cur_dir_buff);
int						ft_env(t_sh *sh, char **av);
int						ft_setenv(t_sh *sh, char **av);
int						ft_exit(t_sh *sh, char **av);
int						ft_unsetenv(t_sh *sh, char **av);
int						ft_echo(t_sh *sh, char **av);
int						detect_bi(char *str, const t_op *cmd_tab);
int						is_builtin(char *av);
char					*ft_getterm(char **env);
int						ft_init_term(void);
int						ft_terms_init(t_terms *terms);
int						ft_terms_toggle(t_terms *terms, int on);
void					ft_terms_clear(t_terms **terms);
int						ft_terms_toggle_key(char *key);
int						ft_putc(int c);
t_terms					*ft_terms_get(void);
int						ft_cd(t_sh *sh, char **av);
char					*get_cur_dir(char *cur_dir_buff);
int						ft_env(t_sh *sh, char **av);
int						ft_color(t_sh *sh, char **av);
int						ft_setenv(t_sh *sh, char **av);
int						ft_exit(t_sh *sh, char **av);
int						ft_unsetenv(t_sh *sh, char **av);
int						ft_echo(t_sh *sh, char **av);
int						detect_bi(char *str, const t_op *cmd_tab);
int						is_builtin(char *av);
int						ft_count_string(t_dlist *lst);
int						handle_char(char c, t_dlist_wrap *wrap);
int						handle_del(t_dlist_wrap *wrap);
int						handle_del_right(t_dlist_wrap *wrap);
int						move_left(t_dlist_wrap *wrap);
int						move_right(t_dlist_wrap *wrap);
int						move_sright(t_dlist_wrap *wrap);
int						move_sleft(t_dlist_wrap *wrap);
int						ft_read(t_sh *sh);
void					init_tab(void);
int						get_func(char buf[8]);
int						is_printable(char buf[8]);
int						is_break(char buf[8]);
int						is_updown(char buf[8]);
int						refresh_line(t_dlist_wrap *wrap, t_sh *sh);
int						reset_cursor(t_dlist_wrap *wrap, t_sh *sh);
int						move_end(t_dlist_wrap *wrap);
int						move_home(t_dlist_wrap *wrap);
t_dlist					*cur_list(t_dlist_wrap *wrap);
int						move_updown(t_dlist_wrap *wrap, char buf[8], t_sh *sh);
int						ft_handle_quote(t_dlist *list);
int						ft_quote(t_dlist_wrap *wrap, t_sh *sh);
int						count_tmp(t_dlist_wrap *wrap, int pos);
int						ft_print_list(t_dlist_wrap *wrap, t_sh *sh);
int						handle_del(t_dlist_wrap *wrap);
int						handle_del_right(t_dlist_wrap *wrap);
int						move_right(t_dlist_wrap *wrap);
int						move_left(t_dlist_wrap *wrap);
int						move_sdown(t_dlist_wrap *wrap);
int						move_sup(t_dlist_wrap *wrap);
int						apply_cap(char buf[8], t_dlist_wrap *wrap, t_sh *sh);
int						cut_list(t_dlist_wrap *wrap);
int						paste_list(t_dlist_wrap *wrap);
char					*get_str_in_quotes(char *str);
char					**fmt_input_quote(char **av);
void					fmt_input_spec_chr(char **str);
char					**ft_list_to_tab(t_dlist *list);
int						ft_setupenv(t_environ *env);
char					*get_env_var(char *str, char **environ);
int						cmp_env_var(char *var, char *to_cmp, size_t n);
void					add_var_to_env(t_sh *sh, char **var);
char					*add_eq_between(char **arg);
char					**tab_str_remove(char **base, int (*cmp)(),
							char *to_cmp, size_t limit);
char					*ft_getenv(char **env, char *var);
void					ft_getsignal(void);
void					ft_signal(int sig);
bool					jump_loop(void);
void					sig_intercepter(void);
void					sighandler(int sigval);
int						ft_prompt(t_sh *sh);
int						len_prompt(t_sh *sh);
void					sig_intercepter(void);
bool					jump_loop(void);
void					ft_start_process(t_sh *sh);
int						ft_init(t_sh *sh, t_hist *hist);
void					ft_execution(t_sh *sh);
void					hl_print_str(t_dlist *list);
int						exec_cmd(t_dlist *input);
int						skip_quotes(char *str, char quote);
t_dlist					*init_proc_list(char *input, char token);
char					*check_bin(char **paths, char *input);
char					*get_cmd_name(char *input);
void					close_fd(int *pfd);
void					flush_sh(t_sh *sh);
bool					is_binary_file(char *bin_name);
bool					is_valid_path(char *path_bin);
int						exec_builtin(int index, t_dlist *curr, int *save);
int						pipe_processes(t_dlist *curr, int *pfd);
char					*handle_heredoc(char *str, t_sh *sh);
void					exec_procs(t_dlist *pipes);
int						r_right(char *input);
int						r_dright(char *input);
int						r_left(char *input);
int						r_dleft(char *input);
char					**extract_redir(t_dlist *curr, int *save);
int						get_redir(char *av);
int						redir_id(char *str);
void					redir_fd(int old_fd, int new_fd);
int						fd_to_file(char *file, int perm);
int						check_src_fd(char *input, int default_fd);
int						do_redirs(t_dlist *redirs);
bool					next_is_fd(char *input, int src);
int						save_builtin_stdio(int index, t_dlist *curr);
void					init_stdio(int *stdio);
void					dup_stdio(int *stdio);
void					close_stdio(int *stdio);
char					*is_redir(t_dlist **redir, char *input);
char					*is_arg(t_dlist **arg, char *input);
char					*skip_cmd_name(t_dlist **arg, char *input);
int						printlvl(void);
int						ft_quit(void);
void					ft_signal2(int sig);
int						exit_error(char *erro_msg, int exit_id, char *cmd_name);
int						check_mv_tmp(t_dlist_wrap *wrap);
void					nextline(int mode);
void					ft_printcolor(t_dlist *list);
void					printblue(t_dlist *list);
void					printred(t_dlist *list);
void					printyellow(t_dlist *list);
void					printwhite(t_dlist *list);
void					printgreen(t_dlist *list);
void					printcyn(t_dlist *list);
int						is_dlist_space(t_dlist *list);
int						is_dlist_word(t_dlist *list);
int						is_dlist_opt(t_dlist *list);
int						is_dlist_red(t_dlist *list);
void					check_norm(t_dlist **list);
void					check_cmd(t_dlist **list);
void					check_args(t_dlist **list);
void					check_redir(t_dlist **list);
int						is_token_redir(t_dlist *list);
int						is_token(t_dlist *list);
void					printspace(t_dlist **list);
int						ft_hash(t_sh *sh, char **av);
char					*get_in_hash(char *str);
int						add_in_path(char *str, char *path);
t_dlist					*create_new_hash(char *str, char *path);
void					hash_check(char *str);

#endif
