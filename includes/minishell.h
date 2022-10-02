/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 22:24:10 by junseo            #+#    #+#             */
/*   Updated: 2022/10/01 18:25:06 by junseo           ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/stat.h>
# include <stdbool.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

enum	e_token_type
{
	TO_COMMON,
	TO_REDIRIN,
	TO_REDIROUT,
	TO_HEREDOC,
	TO_APPEND,
	PIPE,
	DOLLAR,
	DQUOTE,
	QUOTE,
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
typedef struct s_cmd_list		t_cmd_list;
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
	t_env_node		*env_head;
	int				exit_status;
};

// env
void				init_env(char **envp);
char				*extract_env_key(char *env);
char				*extract_env_value(char *env);
t_env_node			*create_env_node(char *key, char *value);
char				*get_env_via_key(char *key);

// echoctl
void				enable_echoctl(void);
void				disable_echoctl(void);

// * parse
int					parse(t_cmd_list *cmd_list);

// * parse | token list
t_token_node		*create_token_node(char	*line, int *i, \
					enum e_token_type type);
t_cmd_node			*create_command_node(char *cmd, enum e_cmd_type type);
void				token_lstadd_back(t_token_node **token_head, \
					t_token_node **new_node);
void				cmd_lstadd_back(t_cmd_node **cmd_head, \
					t_cmd_node *new_node);

// * parse | line -> token
int					tokenization(t_token_node **token_head, char *line);

// * parse | token -> cmd
int					transformation(t_cmd_list *cmd_list, \
					t_token_node *token_head, char *line);

// * parse | token utils
enum e_token_type	get_token_type(char *line, int i);
char				*extract_common_token_from_line(char *line, int *i);
char				*extract_quote_token_from_line(char *line, int *i);
char				*extract_special_token_from_line(char *line, int *i, \
					enum e_token_type type);

// * parse | join utils
int					need_join(t_token_node *curr_token, char *line, \
					int option);
void				join_cmd(t_cmd_node **cmd_head, char *cmd);
void				join_dquote(t_cmd_node **cmd_head, \
					t_token_node **token_head);

// * parse | make a new str utils
void				make_new_dollar_string(int *i, t_token_node **curr, \
					char **new_str);
void				make_new_common_string(int *i, t_token_node **curr, \
					char **new_str);
void				make_new_str(char **new_str, t_token_node **token_head);

// * parse | quote & double quote
void				new_quote(t_cmd_node **cmd_head, t_token_node **token_head);
void				new_dquote(t_cmd_node **cmd_head, \
					t_token_node **token_head);
void				dquote_dollar(char **new_str, char *key);

// * parse | dollar
char				*transform_dollar_token(char *str, int i, char *line);

// * parse | checker
int					command_validator(t_cmd_list *cmd_list);

// * signal
void				enable_heredoc_signal(void);
void				enable_signal(void);
// error
void				exit_with_err(char *msg, char *msg2, int error_no);
int					parse_error(int option);
// custom utils
void				*ft_malloc(size_t size, size_t n);
char				*ft_strjoin_with_free(char *s1, char *s2);

// initializer
t_cmd_list			*init_cmd(void);
void				init_cmd_size(t_cmd_list *cmd_list, \
					t_token_node *token_head);

//builtin
void				execute_builtin(t_cmd_node	*node);
void				execute_one_builtin(t_cmd_node	*node);
//builtin |pwd
void				builtin_pwd(void);
//builtin 			|echo
void				builtin_echo(t_cmd_node *node);
//builtin |env
void				builtin_env(void);
//builtin |exit
void				builtin_exit_one_cmd(t_cmd_node *head);
void				builtin_exit(t_cmd_node *head);
//builtin |export
void				builtin_export_one_cmd(t_cmd_node *node);
void				builtin_export(t_cmd_node *node);
int					has_equal_sign(char *str);
t_env_node			*is_in_envp(char *str);
int					is_right_form(char *str);
void				new_export(char *str);
int					modify_envp(char *str, char *key);
//builtin |unset
void				builtin_unset_one_cmd(t_cmd_node *head);
void				builtin_unset(t_cmd_node *head);
int					unset_error(char *cmd);
void				unset_error_single(char *cmd);

//builtin |cd
void				builtin_cd_one_cmd(t_cmd_node *head);
void				builtin_cd(t_cmd_node *head);
void				old_dir(void);
void				home_dir(char *str);
char				*get_pwd(void);

//execute
void				execute_cmd(t_cmd_list *cmd_line_list);
void				execve_error(char *strerror, t_cmd_node *cmd_list);
char				**set_envp(void);
//execute |with pipe
void				execute_with_pipe(t_cmd_list *list);
//execute |without pipe
void				execute_without_pipe(t_cmd_list *list);
//execute |redirect in
void				redir_in(t_cmd_node *node);
char				*have_redirect_in(t_cmd_node *node);
t_cmd_node			*remove_redirection_in_cmd(t_cmd_node *node);
//execute |redirect out
void				redir_out(t_cmd_node *node);
t_cmd_node			*have_redirect_out(t_cmd_node *node);
//execute |check cmd
char				**cmd_change_to_array(t_cmd_node *node);
int					add_cmd(t_cmd_node **cmd_head, t_cmd_node *new_node);
char				*is_valid_cmd(char *cmd);
//execute |pipe, malloc
void				close_fd(int ***fd, int size);
void				free_variables(int size, int ***fd, pid_t **pid, \
					int **status);
void				close_wait(int ***fd, pid_t **pid, int *status, int size);
void				pipe_process(int size, int ***fd);
void				malloc_variables(int size, int ***fd, pid_t **pid, \
					int **status);
t_cmd_node			*cmd_dup(t_cmd_node *src_node);
//utils | free
void				free_array(int **tmp, int idx);
void				free_split(char **tmp);
//utils | heredoc
int					do_heredoc(t_cmd_node **curr_cmd);
void				move_heredoc_curser(int fd);
void				remove_temp_file(void);

#endif
