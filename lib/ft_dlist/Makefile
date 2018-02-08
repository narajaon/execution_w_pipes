NAME:=libftdlist.a

GREEN:="\033[32m"
ORANGE:="\033[33m"
RED:="\033[31m"
CLEAR:="\033[0m"

CC:=gcc
CFLAGS:=-Wall -Wextra -Werror
CFLAGS+=-g3

OBJ_D:=obj
LIB_D:=..

INC_D:=\
	-I inc\
	-I ../libft/inc

VPATH:=src:inc

ITEM:=\
ft_dlist_create.o\
ft_dlist_clear.o\
ft_dlist_findchar.o\
ft_dlist_from.o\
ft_dlist_free.o\
ft_dlist_insert.o\
ft_dlist_last.o\
ft_dlist_len.o\
ft_dlist_replace.o\
ft_dlist_swap.o\
ft_dlist_to_str.o\
ft_dlist_delone.o

OBJ:=$(addprefix $(OBJ_D)/, $(ITEM))

RM=/bin/rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo ${GREEN}$(NAME) built${CLEAR}

${OBJ_D}/%.o: %.c #$(HEADER)
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c -o $@ $< $(INC_D)

clean:
	@$(RM) -r $(OBJ_D)
	@echo ${ORANGE}Cleaning $(NAME)${CLEAR}

fclean: clean
	@$(RM) $(NAME)
	@echo ${RED}Full cleaning $(NAME)${CLEAR}

re: fclean all
