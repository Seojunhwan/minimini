# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#              #
#    Updated: 2022/09/19 20:08:10 by junseo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror

INCLUDE 		=	-I./includes

FILES			=	minishell	\
					utils/init_env	\
					utils/custom_fuc	
					

DIR_SRCS		=	./srcs/

SRCS			=	$(addprefix $(DIR_SRCS), $(addsuffix .c, $(FILES)))

OBJS			=	$(SRCS:.c=.o)

LIBFT_DIR		=	./libft/

LIBRARY			=	-lreadline -L$(LIBFT_DIR) -lft

all		: $(NAME)

$(NAME)	:  $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(LIBRARY) -o $@ $^

%.o		: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean	:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean	: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re		:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re