NAME:=libftprintf.a

GREEN:="\033[32m"
ORANGE:="\033[33m"
RED:="\033[31m"
CLEAR:="\033[0m"

CC:=gcc
CFLAGS:=-Wall -Wextra -Werror
CFLAGS+=-g3

MKDIR:=mkdir -p
RANLIB:=ranlib

OBJ_D:=obj
INC_D:=inc
LIB_D:=..

INCLUDES = 	-I inc \
			-I ../libft/inc 

VPATH:=src:inc

HEADER:=libft.h

ITEM:=\
	conv_char.o \
	conv_fun.o \
	conv_int.o \
	conv_str.o \
	conv_uint.o \
	conv_unit2.o \
	get_cast.o \
	get_opt.o \
	get_values.o \
	nbr_size.o \
	opt_fun.o \
	opt_min.o \
	opt_width_prec_digit.o \
	opt_width_prec_str.o \
	print_out.o \
	ft_printf.o 

OBJ:=$(addprefix ./obj/, $(ITEM))

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) rc $(NAME) $(OBJ)
	@$(RANLIB) $(NAME)
	@echo ${GREEN}$(NAME) built${CLEAR}

${OBJ_D}/%.o: %.c 
	@$(MKDIR) $(OBJ_D)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
clean:
	@echo ${ORANGE}Cleaning $(NAME)${CLEAR}
	@$(RM) -r $(OBJ_D)

fclean: clean
	@echo ${RED}Full cleaning $(NAME)${CLEAR}
	@$(RM) $(NAME)

re: fclean all

