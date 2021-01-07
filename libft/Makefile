# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 18:31:56 by enoelia           #+#    #+#              #
#    Updated: 2021/01/06 20:16:11 by enoelia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = libft.h
C_SRC = ft_itoa.c \
		ft_split.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_memset.c \
		ft_strtrim.c \
		ft_putnbr_fd.c \
		ft_putchar_fd.c \
		ft_chrarrlen.c \
		ft_calloc.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_memcpy.c \
		ft_strchr.c \
		ft_putstr.c \
		ft_strdup.c	\
		ft_memccpy.c \
		ft_strmapi.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_incrase_position.c	

BONUS_C_SRC = ft_lstnew.c \
		ft_lstmap.c \
		ft_getdist.c \
		ft_lstiter.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_tlst_to_chararr.c \
		get_next_line.c \
		strs.c \
		strarrs.c \
		strarrs2.c 
O_SRC = $(C_SRC:.c=.o)
BONUS_O_SRC = $(BONUS_C_SRC:.c=.o)
override O_ALL ?= $(O_SRC) 
FLAGS = -Wall -Wextra -Werror 


.PHONY: all clean fclean re bonus so

all: $(NAME)

$(NAME): $(O_ALL) $(HEADER)
	ar -rcs $(NAME) $?
	ranlib $(NAME)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

bonus:
	@make O_ALL="$(O_SRC) $(BONUS_O_SRC)" all

clean:
	/bin/rm -f $(O_SRC) $(BONUS_O_SRC) libft.so

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

so:
	gcc -c $(C_SRC) $(BONUS_C_SRC) $(HEADER) -fpic
	gcc -shared -o libft.so $(O_SRC) $(BONUS_O_SRC)
	rm -f $(O_SRC) $(BONUS_O_SRC)
