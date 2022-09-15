# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 19:59:25 by junseo            #+#    #+#              #
#    Updated: 2022/09/15 15:21:19 by junseo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -Lreadline
INCLUDE 		=	-I./includes

FILES			=	minishell	\

DIR_SRCS		=	./srcs/

SRCS			=	$(addprefix $(DIR_SRCS), $(addsuffix .c, $(FILES)))

OBJS			=	$(SRCS:.c=.o)

all		: $(NAME)

$(NAME)	:  $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

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