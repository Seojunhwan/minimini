# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#              #
#    Updated: 2022/09/26 05:33:32 by junseo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
DEBUG_FLAGS		=	-g -fsanitize=address

INCLUDE 		=	-I./includes

DIR_BASE		=	./srcs/
DIR_PARSE		=	parse/
DIR_ENV			=	env/
DIR_UTIL		=	utils/



PARSE_FILSE		=	initializer	\
					parse	\
					tokenizer

ENV_FILES		=	env_utils	\
					initializer

UTIL_FILES		=	custom_fuc	\
					exit_utils	\
					terminal_utils

SRCS			=	$(addprefix $(DIR_BASE), $(addsuffix .c, $(NAME)))	\
					$(addprefix $(DIR_BASE), $(addprefix $(DIR_PARSE), $(addsuffix .c, $(PARSE_FILSE))))	\
					$(addprefix $(DIR_BASE), $(addprefix $(DIR_ENV), $(addsuffix .c, $(ENV_FILES))))	\
					$(addprefix $(DIR_BASE), $(addprefix $(DIR_UTIL), $(addsuffix .c, $(UTIL_FILES))))	\

OBJS			=	$(SRCS:.c=.o)

LIBFT_DIR		=	./libft/

LIBRARY			=	-lreadline -L$(LIBFT_DIR) -lft

all		: $(NAME)

$(NAME)	:  $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(LIBRARY) -o $@ $^

debug	: $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(LIBRARY) -o $(NAME) $^

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