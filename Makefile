# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/26 19:32:53 by enoelia           #+#    #+#              #
#    Updated: 2021/01/06 20:18:46 by enoelia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = sources
INC = includes
C = main.c \
	parser/parser_env.c \
	parser/parser_quotes.c \
	parser/parser_escape_symbol.c \
	parser/parser_redirect.c \
	parser/parser_semicolon.c \
	parser/parser_spaces.c \
	parser/parser_pipe.c \
	parser/parser.c \
	parser/structure.c\
	builtins_imp/cd.c \
	builtins_imp/echo.c \
	builtins_imp/env.c \
	builtins_imp/exit.c \
	builtins_imp/export_unset_2.c \
	builtins_imp/export.c \
	builtins_imp/pwd.c \
	builtins_imp/unset.c \
	exec_commands/exec_imp.c \
	exec_commands/exec.c \
	exec_commands/implement.c \
	exec_commands/exec_signals.c \
	exec_commands/exec_utils.c \
	exec_commands/execve.c

C_SRC =  $(addprefix $(SRC)/, $C)

O_SRC = $(C_SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

LIB_PATH = libft

LIB = $(LIB_PATH)/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB) $(INC)/$(NAME).h $(O_SRC)
	gcc -o $(NAME) $(FLAGS) -I$(INC) $(O_SRC) $(LIB)

$(LIB):
	make -C $(LIB_PATH) bonus 

%.o: %.c $(INC)/$(NAME).h
	gcc $(FLAGS) -I$(INC) -I$(LIB_PATH) -c $< -o $@

clean: 
	/bin/rm -f $(O_SRC)
	make -C $(LIB_PATH) clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIB_PATH) fclean

re: fclean all

debug:
	gcc -o $(NAME) $(FLAGS) -I$(INC) -I$(LIB_PATH) $(C_SRC) $(LIB) -g