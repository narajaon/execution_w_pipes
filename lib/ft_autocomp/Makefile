NAME = libautocompletion.a

SRC_D:=src
OBJ_D:=obj
INC_D:=inc
LIB_D:=..
LOCAL_LIB:=lib/

HEAD = \
    inc/autocompletion.h\
    inc/levenshtein.h\
    inc/macros.h

CC:=gcc
CFLAGS:=-Wall -Wextra -Werror
CFLAGS += -g3
#CFLAG += -fsanitize=address

INC:=-I $(INC_D)
INCLUDES:=$(INC)

O_FILES := \
	add_branch_to_input.o\
	add_word_to_tree.o\
	history_to_tree.o\
	leven.o\
	list_to_lev_tree.o\
	new_lev_node.o\
	print_lev_tree.o\
	read_stock_input.o\
	search_thru_history.o\
	history_handler.o\
	tree_to_dlist.o\
	free_str.o\
	free_autocmp.o\
	completion_handler.o\
	ft_hlstadd.o\
	ft_hlstadd_back.o\
	ft_hlstnew.o\
	hl_dup.o\
	hl_utils.o\
	print_hlist.o

C_FILES := \
	add_branch_to_input.c\
	add_word_to_tree.c\
	history_to_tree.c\
	leven.c\
	list_to_lev_tree.c\
	new_lev_node.c\
	print_lev_tree.c\
	read_stock_input.c\
	search_thru_history.c\
	history_handler.c\
	tree_to_dlist.c\
	free_str.c\
	free_autocmp.c\
	completion_handler.c

L_FILES := \
	ft_hlstadd.c\
	ft_hlstadd_back.c\
	ft_hlstnew.c\
	hl_dup.c\
	hl_utils.c\
	print_hlist.c

OBJ := $(addprefix $(OBJ_D)/, $(O_FILES))
SRC := $(addprefix $(SRC_D)/, $(C_FILES))
SRC := $(addprefix $(LOCAL_LIB), $(L_FILES))
VPATH :=$(SRC_D):$(INC_D):$(LOCAL_LIB)

include libs.mk

all: $(NAME)

$(NAME): $(OBJ) $(HEAD) Makefile
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[33m$(NAME)\033[0m built"

$(OBJ_D)/%.o: %.c
	@mkdir -p $(OBJ_D)
	@$(CC) $(FLAGS) -c -o $@ $< $(INCLUDES)

clean:
	@echo "[autocomp] Deleting:\033[33m *.o\033[0m"
	@rm -f $(OBJ)

fclean: clean
	@echo "[autocomp] Deleting:\033[33m $(NAME)\033[0m"
	@rm -f $(NAME)

re: fclean all

git :
	@git add .
	@git commit -m "${MSG}"

gitp : fclean git
	git push

.PHONY: clean fclean re git gitp
