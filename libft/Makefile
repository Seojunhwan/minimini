FILES		=	ft_strlen \
				ft_strlcpy \
				ft_strlcat \
				ft_strchr \
				ft_strrchr \
				ft_isalpha \
				ft_isdigit \
				ft_isalnum \
				ft_isascii \
				ft_isprint \
				ft_toupper \
				ft_tolower \
				ft_memset \
				ft_strncmp \
				ft_memchr \
				ft_bzero \
				ft_memcpy \
				ft_memcmp \
				ft_strnstr \
				ft_atoi \
				ft_calloc \
				ft_strdup \
				ft_substr \
				ft_strjoin \
				ft_strjoin \
				ft_strtrim \
				ft_split \
				ft_itoa \
				ft_strmapi \
				ft_striteri \
				ft_putchar_fd \
				ft_putstr_fd \
				ft_putendl_fd \
				ft_putnbr_fd \
				ft_memmove 

FILES_BONUS	=	ft_lstnew \
				ft_lstadd_front \
				ft_lstsize \
				ft_lstlast \
				ft_lstadd_back \
				ft_lstdelone \
				ft_lstclear \
				ft_lstiter \
				ft_lstmap

DIR_OBJS	= ./
OBJS		= $(addprefix $(DIR_OBJS), $(addsuffix .o, $(FILES)))
OBJS_BONUS	= $(addprefix $(DIR_OBJS), $(addsuffix .o, $(FILES_BONUS)))
DIR_SRCS	= ./
SRCS		= $(addprefix $(DIR_SRCS), $(addsuffix .c, $(FILES)))
SRCS_BONUS	= $(addprefix $(DIR_SRCS), $(addsuffix .c, $(FILES_BONUS)))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

AR			= ar crus
RM			= rm -f

NAME		= libft.a

.c.o:		$(SRCS) $(SRCS_BONUS)
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

bonus:		$(OBJS_BONUS)
			$(AR) $(NAME) $(OBJS_BONUS)

clean: 
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY:		all bonus clean fclean re
