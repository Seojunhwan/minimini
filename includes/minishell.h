/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:24:10 by junseo            #+#    #+#             */
/*   Updated: 2022/09/25 02:36:10 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h> // error?
# include <errno.h> // error
# include "../libft/libft.h"

enum	e_token_type
{
	TO_COMMON,
	TO_REDIRIN,
	TO_REDIROUT,
	TO_HEREDOC,
	TO_APPEND,
	PIPE,
	DQUOTE,
	QUOTE,
	DOLLAR
};

enum	e_cmd_type
{
	COMMON,
	REDIRIN,
	REDIROUT,
	HEREDOC,
	APPEND,
	REDIRARG,
	BUILTIN,
	OPTION
};

typedef struct s_token_node		t_token_node;
typedef struct s_cmd_node		t_cmd_node;
typedef struct s_cmd_list	t_cmd_list;
typedef struct s_state			t_state;
typedef struct s_env_node		t_env_node;
t_state							g_state;

struct s_token_node
{
	enum e_token_type	type;
	char				*token;
	t_token_node		*prev;
	t_token_node		*next;
	int					idx;
};

struct s_cmd_node
{
	enum e_cmd_type	type;
	char			*cmd;
	t_cmd_node		*prev;
	t_cmd_node		*next;
};

struct s_cmd_list
{
	int			size;
	t_cmd_node	**cmd_heads;
};

struct s_env_node
{
	char		*key;
	char		*value;
	t_env_node	*next;
};

struct s_state
{
	t_env_node		**env_head;
	int				exit_status;
};

// env
void		init_env(char **envp);
char		*extract_env_key(char *env);
char		*extract_env_value(char *env);
t_env_node	*create_env_node(char *env);

// echoctl
void	enable_echoctl(void);
void	disable_echoctl(void);

// parse
void	parse(t_cmd_list **cmd_list);

// error
void	exit_with_err(char *msg, char *msg2, int error_no);

// custom utils
void	*ft_malloc(size_t size, size_t n);

// initializer
t_cmd_list *init_cmd();


#endif
