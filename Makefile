# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#              #
#    Updated: 2022/09/29 19:52:20 by junseo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
DEBUG_FLAGS		=	-g -fsanitize=address

INCLUDE 		=	-I./includes -I/Users/junseo/.brew/opt/readline/include

DIR_BASE		=	./srcs/
DIR_PARSE		=	parse/
DIR_ENV			=	env/
DIR_UTIL		=	utils/
DIR_HEREDOC		=	heredoc/

PARSE_FILSE		=	cmd_checker	\
					command_list	\
					dollar	\
					initializer	\
					join	\
					make_new_str	\
					parse	\
					token_list	\
					tokenizer	\
					transformer

ENV_FILES		=	env_utils	\
					initializer

HEREDOC_FILES	=	heredoc

UTIL_FILES		=	custom_fuc	\
					dquote	\
					exit_utils	\
					quote	\
					terminal_utils	\
					token	\
					heredoc	\
					signal

SRCS			=	$(addprefix $(DIR_BASE), $(addsuffix .c, $(NAME)))	\
					$(addprefix $(DIR_BASE), $(addprefix $(DIR_PARSE), $(addsuffix .c, $(PARSE_FILSE))))	\
					$(addprefix $(DIR_BASE), $(addprefix $(DIR_ENV), $(addsuffix .c, $(ENV_FILES))))	\
					$(addprefix $(DIR_BASE), $(addprefix $(DIR_UTIL), $(addsuffix .c, $(UTIL_FILES))))	\
					$(addprefix $(DIR_BASE), $(addprefix $(DIR_HEREDOC), $(addsuffix .c, $(HEREDOC_FILES))))	\

OBJS			=	$(SRCS:.c=.o)

LIBFT_DIR		=	./libft/

LIBRARY			=	-L/Users/junseo/.brew/opt/readline/lib -lreadline -L$(LIBFT_DIR) -lft

all		: $(NAME)

$(NAME)	:  $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBRARY)

debug	: $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(NAME) $^ $(LIBRARY) 

%.o		: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -g -c -o $@ $^

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