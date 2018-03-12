NAME:=21sh
CC:=gcc

RM:=/bin/rm -f
MKDIR:=mkdir -p

ifeq ($(DEBUG),yes)
CFLAGS:=-g3 -fsanitize=address
else
CFLAGS:= -g -O2 -Wall -Wextra -Werror
endif
INC_D:=inc
SCR_D:=src
LIB_D:=lib
OBJ_D:=obj
HEAD =$(INC_D)/header.h

INCLUDES = -I inc \
		-I lib/ft_printf/inc \
		-I lib/libft/inc \
		-I lib/ft_dlist/inc \
		-I lib/ft_autocomp/inc

LIBRARIES = -L lib/ft_printf -lftprintf \
			-L lib/libft -lft \
			-L lib/ft_dlist -lftdlist \
			-L lib/ft_autocomp -lautocompletion \
			-lcurses

ITEM = \
		main.o \
		envdup.o \
		getterm.o \
		ft_terms.o \
		ft_terms_get.o\
		signal.o \
		prompt.o \
		heredoc_read.o \
		utility.o \
		cd.o \
		echo.o \
		env.o \
		exit.o \
		setenv.o \
		hash.o \
		unsetenv.o \
		built_in.o \
		get_str_in_quotes.o \
		add_char.o \
		buf.o \
		copy_paste.o \
		del_char.o \
		hist.o \
		mv.o \
		mv_home.o\
		mv_multi.o \
		mv_word.o \
		init_cap.o \
		read.o \
		refresh_line.o \
		exec_procs.o \
		fd_manip.o \
		split_by_semicol.o \
		utils.o \
		parse_redir.o \
		str_conversion.o \
		redir_funs.o \
		redir_funs2.o \
		spec_char.o \
		split_into_args.o \
		exec_bins.o \
		exec_builtins.o \
		exit_erro.o \
		heredoc.o \
		shlvl.o \
		printcolor.o \
		wcolor.o \
		is_dlist.o \
		norm.o \
		is_tok.o \
		redir_col.o

OBJ:=$(addprefix $(OBJ_D)/, $(ITEM))

vpath %.c src \
		src/env \
		src/signal \
		src/prompt \
		src/builtin \
		src/str_format \
		src/reader \
		src/redirs \
		src/exec \
		src/parser \
		src/color

vpath %.h inc ../libft/inc

all: $(NAME)

$(NAME): $(OBJ) $(HEAD) Makefile
	@$(MAKE) -C lib/libft
	@$(MAKE) -C lib/ft_printf
	@$(MAKE) -C lib/ft_dlist
	@$(MAKE) -C lib/ft_autocomp
	@$(CC) $(CFLAGS) -o $(NAME) $(INCLUDES) $(LIBRARIES) $(OBJ)
	@echo  "it's done"

./${OBJ_D}/%.o: %.c 
	@$(MKDIR) $(OBJ_D)
	@$(CC) $(CFLAGS) -c -o $@ $<  $(INCLUDES)

clean:
	@$(MAKE) -C lib/ft_printf clean
	@$(MAKE) -C lib/libft clean
	@$(MAKE) -C lib/ft_dlist clean
	@$(MAKE) -C lib/ft_autocomp clean
	@$(RM) -r $(OBJ_D)
	@echo "it's clean"

fclean: clean
	@$(MAKE) -C lib/ft_printf fclean
	@$(MAKE) -C lib/libft fclean
	@$(MAKE) -C lib/ft_dlist fclean
	@$(MAKE) -C lib/ft_autocomp fclean
	@$(RM) $(NAME)
	@echo "it's fclean"

re: fclean all

git :
	@git add .
	@git commit -m "${MSG}"

gitp : fclean git
	git push
