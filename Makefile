# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fake_file_name (file name is useless too)          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: 42header-remover <whatever@example.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#              #
#    Updated: 1970/01/01 00:00:00 by file history     ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
READLINE		=	-lreadline
INCLUDE 		=	-I./includes

FILES			=	minishell	\

DIR_SRCS		=	./srcs/

SRCS			=	$(addprefix $(DIR_SRCS), $(addsuffix .c, $(FILES)))

OBJS			=	$(SRCS:.c=.o)

all		: $(NAME)

$(NAME)	:  $(OBJS)
	$(CC) $(CFLAGS) $(READLINE) -o $@ $^

%.o		: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean	:
	rm -f $(OBJS)

fclean	: clean
	rm -f $(NAME)

re		:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re