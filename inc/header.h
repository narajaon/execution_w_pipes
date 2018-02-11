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

extern char					**environ;

typedef struct termios		t_termios;
typedef struct s_sh			t_sh;
typedef struct winsize		t_win;
typedef struct s_token		t_token;
typedef struct s_dlist_wrap	t_dlist_wrap;
typedef struct s_process	t_process;
typedef struct s_redir		t_redir;
typedef int					(*t_intfunc)();

int							g_fd; // pour interface de controle
int							g_tmp;
int							g_tmp2;

bool						g_loop;
int							g_cur_pid;
t_sh						*g_sh;
pid_t						g_pfd[2];

/*
unsigned short ws_row;	
unsigned short ws_col;	
unsigned short ws_xpixel;	 horizontal size, pixels 
unsigned short ws_ypixel;	vertical size, pixels 
*/

# define K_UP		65
# define K_DOWN		66
# define K_RIGHT	67
# define K_LEFT		68
# define K_END		70
# define K_HOME		72
# define K_PUP		53
# define K_PDOWN	54
# define K_DEL		51 
# define K_CUT		11
# define K_YANK		12

# define ERR_MALLOC "erreur dans l'attribution de memoire malloc \n"

# define SCHAR_NB 11
//(char c,  int (*f)(t_dlist_wrap *, t_sh *))

typedef struct			s_schar
{
	char				sequ[3];
	char				asc;
}						t_schar;

enum					e_term_status
{
	TERM_NULL,
	TERM_INIT,
	TERM_READY
};

enum					e_quote_status
{
	Q_OK,
	QUOTE,
	DQUOTE,
	SLASH,
	Q_PIPE,
	Q_HEREDOC,
	QUOT_SIZE
};

enum 					e_mov
{
	DEL,
	LEFT,
	RIGHT,
	ADD,
	ADD_END,
	END,
	BEGIN,
	HIST,
	MOV_SIZE
};

enum 					e_type
{
	NEW,
	WORD,
	IO_NUMBER,
	NEWLINE,
	PIPE,
	DPIPE,
	AND,
	LAND,
	OR,
	LOR,
	SEMICOL,
	DSEMICOL,
	BSLASH,
	LREDIR,
	RSREDIR,
	HEREDOC,
	RDREDIR,
	ETYPE_SIZE
};

enum 					e_build_in
{
	B_NONE,
	B_ECHO,
	B_CD,
	B_ENV,
	B_SETENV,
	B_UNSETENV,
	B_EXIT,
	BUILD_IN_SIZE
};

typedef struct			s_op
{
	char				*cmd;
	enum e_build_in		type;
	int					(*f)(t_sh *, char **);
}						t_op;

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
	int 				size;
}						t_environ;

typedef struct			s_dlist_wrap
{
	t_dlist				*head;
	t_dlist				*cursor;
	t_dlist				*last;
	t_dlist				*tmp;
	t_dlist				*yanked;
	int 				pos;
	enum e_mov			last_mov;
}						t_dlist_wrap;

typedef struct			s_token
{
	t_dlist				*first_letter;
	t_dlist				*last_letter;
	t_token				*next;
	enum e_type			e_type;
}						t_token;

typedef struct			s_redir
{
	char 				**name;
	t_redir				*next;
	enum e_type			type;
}						t_redir;

typedef struct			s_process
{
	char				**argv;		/* for exec */
	t_redir				*file;
	char 				*cmd;
	pid_t				pid;		/* process ID */
	int 				status;
	int 				ret;		/* reported status value */
	enum e_build_in		bi;
	int 				last;
}						t_process;

typedef struct			s_btree
{
	t_process			*process;
	enum e_type			type;
	int 				start;
	struct s_btree		*left;
	struct s_btree		*right;
}						t_btree;

typedef struct			s_pipe
{
	enum e_type			e_type;
	int					in;
	int					out;
	int					err;
}						t_pipe;

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

typedef struct			s_sh
{
	t_environ			env;
	t_terms				term;
	t_dir				dir;
	t_dlist				*list;
	t_token				*token;
	t_btree				**btree;
	t_hist				*hist;
	//t_hashset			*hash; -> bonus pour les commandes deja utilisées
	int 				ret;
	int  				offset;
}						t_sh;

//init
void 					ft_init_keytab(void);

//term
char					*ft_getterm(char **env);
int						ft_init_term(void);
int						ft_terms_init(t_terms *terms);
int						ft_terms_toggle(t_terms *terms, int on);
void					ft_terms_clear(t_terms **terms);
int						ft_terms_toggle_key(char *key);
int						ft_putc(int c);
t_terms					*ft_terms_get(void);

//build_in
int						ft_cd(t_sh *sh, char **av);
char					*get_cur_dir(char *cur_dir_buff);
int						ft_env(t_sh *sh, char **av);
int						ft_setenv(t_sh *sh, char **av);
int						ft_exit(t_sh *sh, char **av);
int						ft_unsetenv(t_sh *sh, char **av);
int						ft_echo(t_sh *sh, char **av);
int 					ft_exec_build_in(t_sh *sh, t_process *process);
int 					detect_bi(char *str);

//arg_formating
char					*get_str_in_quotes(char *str);
char					**fmt_input_quote(char **av);
void					fmt_input_spec_chr(char **str);

//env
int						ft_setupenv(t_environ *env);
char 					*get_env_var(char *str, char **environ);
int						cmp_env_var(char *var, char *to_cmp, size_t n);
void					add_var_to_env(t_sh *sh, char **var);
char					*add_eq_between(char **arg);
char					**tab_str_remove(char **base, int (*cmp)(),
		char *to_cmp, size_t limit);
char					*ft_getenv(char **env, char *var);

//signal
void					ft_getsignal(void);
void					ft_signal(int sig);

bool					jump_loop(void);
void					sig_intercepter(void);
void					sighandler(int sigval);

//prompt
int						ft_prompt(t_sh *sh);
int						len_prompt(t_sh *sh);
void					sig_intercepter(void);
bool					jump_loop(void);
void					ft_start_process(t_sh *sh);
int						ft_init(t_sh *sh);

//input_reader
int						ft_read(t_sh *sh);
int						handle_char(char c, t_dlist_wrap *wrap, t_sh *sh);
int						handle_del(t_dlist_wrap *wrap, t_sh *sh);
int						handle_del_right(t_dlist_wrap *wrap, t_sh *sh);
int						handle_non_char(char c, t_dlist_wrap *wrap, t_sh *sh);
int						move_up(t_dlist_wrap *wrap, t_sh *sh, int mode);
int						move_down(t_dlist_wrap *wrap, t_sh *sh, int mode);
int						move_updown(t_dlist_wrap *wrap, t_sh *sh, char c);
int						move_left(t_dlist_wrap *wrap, t_sh *sh);
int						move_right(t_dlist_wrap *wrap, t_sh *sh);
int						ft_add_character(char c, t_dlist_wrap *wrap);
int						ft_printlist(t_dlist_wrap *wrap, t_sh *sh);
int						ft_print_list(t_dlist_wrap *wrap, t_sh *sh);
int						ft_handle_quote(t_dlist *list);
int						ft_quote(t_dlist_wrap *wrap, t_sh *sh);
int						ft_no_printable(char c);
int						move_left_word(t_dlist_wrap *wrap, t_sh *sh);
int						move_up_ctrl(t_dlist_wrap *wrap, t_sh *sh);
int						move_down_ctrl(t_dlist_wrap *wrap, t_sh *sh);
int						move_begin(t_dlist_wrap *wrap, t_sh *sh);
int						move_end(t_dlist_wrap *wrap, t_sh *sh);
int						get_next_char(char *c);
int 					ft_put_wrap_end(t_dlist_wrap *wrap, t_sh *sh);
//int						get_coord(t_sh *sh, t_dlist_wrap *wrap);
int						is_last_line(int pos, int end, int col);
int						ft_reset_cursor(t_dlist_wrap *wrap, t_sh *sh, int pos);
void					move_cursor_right(t_dlist_wrap *wrap, t_sh *sh);
void					move_cursor_left(t_dlist_wrap *wrap, t_sh *sh);
int						move_dlist_left(t_dlist_wrap *wrap);
int						move_dlist_right(t_dlist_wrap *wrap);

// cursor
int 					ft_count_string(t_dlist *list);
int						ft_count_wrap(t_dlist_wrap *wrap, t_sh *sh);
int 					ft_refresh_line(t_dlist_wrap *wrap, t_sh *sh);

//copy paste
t_dlist					*cut_list(t_dlist_wrap *wrap, t_sh *sh);
void					paste_list(t_dlist_wrap *wrap, t_sh *sh);

//lexer
void 					ft_handle_backslash(t_dlist **line);
int						ft_lexer(t_sh *sh);
int						ft_print_lexinput(t_dlist **list);
t_token					*ft_create_token(t_dlist *line);
int						ft_get_token(t_token *token, t_token **ttoken);
int						ft_print_lexoutput(t_token **list);
int						ft_detect_type(t_dlist *list);
int 					ft_lisspace(t_dlist *list);
char 					ft_lisquote(t_dlist *list, char etalon);
int 					ft_listok(t_dlist *list);
int 					ft_listop(t_dlist *list);
int						ft_get_currline(void);

//parser
int 					ft_parser(t_sh *sh);
t_process 				*ft_new_process(t_token **token);
char 					*spe_strdup(t_token *token);
void					ft_add_process(t_process *nu,
							t_process **list_proc);
int 					ft_print_parsoutput(t_btree **btree);
void 					ft_print_tree(t_btree *btree);


//job
void					ft_launch_job(t_sh *sh);
char					*ft_create_cmd(t_sh *sh, t_process *process);
void					ft_print_process(t_process **process, int fd[3], char *str);
int 					simple_exec(t_sh *sh, t_btree *btree);

//execution
void 					ft_execution(t_sh *sh);
void					hl_print_str(t_dlist *list);
int						exec_cmd(t_dlist *input);
t_dlist					*init_proc_list(char *input, char token);
char					*check_bin(char **paths, char *input);
char					*get_cmd_name(char *input);
void					write_next(pid_t *input, pid_t *output);
void					read_prev(pid_t *input, pid_t *output);
void					close_fd(int *pfd);

void					*g_handlenonchar[SCHAR_MAX];
t_schar					g_spec_char[SCHAR_NB];

#endif
