/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:26:09 by junseo            #+#    #+#             */
/*   Updated: 2022/09/28 05:08:06 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_readline(char **line)
{
	*line = readline("Minishell$ ");
	if (!*line)
	{
		printf("exit\n");
		exit(0);
	}
}

static int	is_empty_line(char *line)
{
	while (*line != '\0')
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}


int	need_join(t_token_node *curr_token, char *line, int option)
{
	char	c;

	// 이게 의미하는 뜻이 무엇일까?
	if (curr_token->idx - 1 > 0)
		c = line[curr_token->idx - 1];
	else
		c = '\0';
	if (option == 1)
	{
		if (c != '\0' && !(c == ' ' || (c >= 9 && c <= 13)))
			return (1);
		return (0);
	}
	else if (option == 2)
	{
		if (c != '\0' && (c == '\'' || c == '"' || \
			!(c == ' ' || (c >= 9 && c <= 13))))
			return (1);
		return (0);
	}
	else
	{
		if (c != '\0' && (c == '\'' || c == '"'))
			return (1);
		return (0);
	}
}

t_cmd_node	*create_command_node(char *cmd, enum e_cmd_type type)
{
	t_cmd_node	*new_node;

	new_node = (t_cmd_node *)ft_malloc(sizeof(t_cmd_node), 1);
	new_node->cmd = cmd;
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	cmd_lstadd_back(t_cmd_node **cmd_head, t_cmd_node *new_node)
{
	t_cmd_node *last_node;

	if (*cmd_head == NULL)
		*cmd_head = new_node;
	else
	{
		last_node = *cmd_head;

		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
		new_node->prev = last_node;
	}
}

void	init_cmd_size(t_cmd_list *cmd_list, t_token_node *token_head)
{
	t_token_node	*curr;
	
	curr = token_head;
	cmd_list->size = 1;
	while (curr != NULL)
	{
		if (curr->type == PIPE)
			cmd_list->size++;
		curr = curr->next;
	}
	cmd_list->cmd_heads = ft_malloc(sizeof(t_cmd_node *), cmd_list->size);
}

// ! double_quote

void	dquote_dollar(char **new_str, char *key)
{
	char	*value;

	if (ft_strcmp(key, "?") == 0)
	{
		*new_str = ft_strjoin(*new_str, ft_itoa(g_state.exit_status));
		return ;
	}
	value =	ft_strdup(get_env_via_key(key));
	if (value == NULL)
		return ;
	*new_str = ft_strjoin_with_free(*new_str, value);
}

void	make_new_dollar_string(int *i, t_token_node **curr, char **new_str)
{
	char	*temp_str;
	int		start;

	start = ++(*i);
	while ((*curr)->token[*i] != '\0' && (*curr)->token[*i] != '$' && !ft_isspace((*curr)->token[*i]))
		(*i)++;
	temp_str = ft_substr((*curr)->token, start, *i - start);
	if (ft_strcmp(temp_str, "") == 0)
		*new_str = ft_strjoin_with_free(*new_str, "$");
	else
		dquote_dollar(new_str, temp_str);
	free(temp_str);
}

void	make_new_common_string(int *i, t_token_node **curr, char **new_str)
{
	char	*temp_str;
	int		start;

	start = (*i)++;
	while ((*curr)->token[*i] != '\0' && (*curr)->token[*i] != '$')
		(*i)++;
	temp_str = ft_substr((*curr)->token, start, *i - start);
	// if (ft_strcmp(temp_str, "") == 0)
	// 	*new_str = ft_strjoin_with_free(*new_str, "$");
	// else
	// 	dquote_dollar(new_str, temp_str);
	*new_str = ft_strjoin_with_free(*new_str, temp_str);
}

void	make_new_str(char **new_str, t_token_node **token_head)
{
	int				i;
	int				len;
	t_token_node	*curr;

	curr = *token_head;
	i = 0;
	len = ft_strlen(curr->token);
	if (len == 0)
		return ;
	while (i < len)
	{
		if (curr->token[i] == '$')
			make_new_dollar_string(&i, &curr, new_str);
		else
 			make_new_common_string(&i, &curr, new_str);
	}
}

void	join_dquote(t_cmd_node **cmd_head, t_token_node **token_head)
{
	char			*new_str;
	t_token_node	*curr;
	t_cmd_node		*last_cmd;

	new_str = ft_strdup("");
	curr = *token_head;
	make_new_str(&new_str, &curr);
	last_cmd = *cmd_head;
	while (last_cmd->next != NULL)
		last_cmd  = last_cmd->next;
	last_cmd->cmd = ft_strjoin_with_free(last_cmd->cmd, new_str);
}

void	new_dquote(t_cmd_node **cmd_head, t_token_node **token_head)
{
	char			*new_str;
	t_cmd_node		*new_cmd;
	t_token_node	*curr;

	curr = *token_head;
	new_str = ft_strdup("");
	make_new_str(&new_str, &curr);
	new_cmd = create_command_node(new_str, COMMON);
	cmd_lstadd_back(cmd_head, new_cmd);
}

// void	join_quote(t_cmd_node **cmd_head, t_token_node **token_head)
// {
// 	char			*new_str;
// 	t_cmd_node		*last_cmd;
// 	t_token_node	*curr;

// 	curr = *token_head;
// 	new_str = ft_strdup(curr->token);
// 	join_cmd(cmd_head, new_str);
// 	return ;
// }

void	join_cmd(t_cmd_node **cmd_head, char *cmd)
{
	t_cmd_node		*last_cmd;

	last_cmd = *cmd_head;
	while (last_cmd->next != NULL)
		last_cmd = last_cmd->next;
	last_cmd->cmd = ft_strjoin_with_free(last_cmd->cmd, cmd);
}

void	new_quote(t_cmd_node **cmd_head, t_token_node **token_head)
{
	char			*new_str;
	t_cmd_node		*new_cmd;
	t_token_node	*curr;

	curr = *token_head;
	new_str = ft_strdup(curr->token);
	new_cmd = create_command_node(new_str, COMMON);
	cmd_lstadd_back(cmd_head, new_cmd);
}

void	add_quote_cmd(t_cmd_node **cmd_head, t_token_node **token_head, char *line)
{
	t_token_node	*curr;

	curr = *token_head;
	if (need_join(curr, line, 1))
		if (curr->type == QUOTE)
			join_cmd(cmd_head, curr->token);
		else
			join_dquote(cmd_head, &curr);
	else
		if (curr->type == QUOTE)
			new_quote(cmd_head, &curr);
		else
			new_dquote(cmd_head, &curr);
	return ;
}

char	*transform_dollar_token(char *str, int i, char *line)
{
	char	*value;
	t_env_node	*temp;

	if (i == 0 || line[i - 1] != '$')
		return (ft_strdup("$"));
	if (ft_strcmp(str, "\"") == 0)
		return (ft_strdup("$"));
	if (ft_strcmp(str, "?") == 0)
		return (ft_itoa(g_state.exit_status));
	temp = *(g_state.env_head);
	value = get_env_via_key(str);
	if (value == NULL)
		return ft_strdup("");
	return ft_strdup(value);
}



void	add_dollar_cmd(t_cmd_node **cmd_head, t_token_node **token_head, char *line)
{
	t_token_node	*curr;
	t_cmd_node		*new_cmd;
	char			*cmd;

	curr = *token_head;
	if (curr->next == NULL)
		cmd = ft_strdup("$");
	else
		cmd	= transform_dollar_token(curr->next->token, curr->next->idx, line);
	if (need_join(curr, line, 2)) // 만약 현재 node command 에 조인을 해야한다면
	{
		join_cmd(cmd_head, cmd);
		if (curr->next != NULL)
			*token_head = curr->next; // 가독성 구림
		return ;
	}
	new_cmd = create_command_node(cmd, COMMON);
	cmd_lstadd_back(cmd_head, new_cmd);
	if (curr->next != NULL)
		curr = curr->next;
	*token_head = curr;
}

void	add_common_cmd(t_cmd_node **cmd_head, t_token_node **token_head, char *line)
{
	t_token_node	*curr;
	t_cmd_node		*new_cmd;

	curr = *token_head;
	if (need_join(curr, line, 3)) // 만약 현재 node command 에 조인을 해야한다면
	{
		join_cmd(cmd_head, curr->token);
		return ;
	}
	new_cmd = create_command_node(ft_strdup(curr->token), (enum e_cmd_type)curr->type);
	cmd_lstadd_back(cmd_head, new_cmd);
	// if (curr->next != NULL)
	// 	curr = curr->next;
	// *token_head = curr;
	return ;
}

void	convert_token_to_command(t_cmd_node **cmd_head, t_token_node **token_head, char *line)
{
	t_token_node *curr;

	curr = *token_head;
	while (curr != NULL && curr->type != PIPE)
	{
		printf("debug : %s\n", curr->token);
		if (curr->type == DQUOTE || curr->type == QUOTE)
			add_quote_cmd(cmd_head, &curr, line);
		else if (curr->token[0] == '$')
			add_dollar_cmd(cmd_head, &curr, line);
		else
			add_common_cmd(cmd_head, &curr, line);
		curr = curr->next;
	}
	if (curr != NULL)
		curr = curr->next;
	*token_head = curr;
	return ;
}

static int	is_common_cmd(t_cmd_node *cmd)
{
	enum e_cmd_type	type;
	
	if (cmd == NULL)
		return 0;
	type = cmd->type;
	if (type == REDIRIN || type == REDIROUT \
		|| type == HEREDOC || type == APPEND)
		return (0);
	return (1);
}

static int	is_echo_option(t_cmd_node *node)
{
	int	i;

	i = 0;
	if (node != NULL && node->cmd[i++] == '-')
	{
		while (node->cmd[i] != '\0')
		{
			if (node->cmd[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	tolower_str(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != '\0')
	{
		str[idx] = ft_tolower(str[idx]);
		idx++;
	}
}

char	*get_lower_str(char *str)
{
	int		len;
	char	*ret;

	len = ft_strlen(str);
	if (len == 0)
		return (ft_strdup(""));
	ret = ft_strdup(str);
	if (ret == 0)
		return (0);
	tolower_str(ret);
	return (ret);
}

static int	is_builtin(t_cmd_node **curr)
{
	int		ret;
	char	*temp;

	temp = get_lower_str((*curr)->cmd);
	ret = 0;
	if (!ft_strcmp(temp, "echo"))
	{
		(*curr)->type = BUILTIN;
		if (is_echo_option((*curr)->next))
		{
			*curr = (*curr)->next;
			(*curr)->type = OPTION;
		}
		ret = 1;
	}
	else if (!ft_strcmp(temp, "cd") || !ft_strcmp(temp, "pwd") || \
		!ft_strcmp(temp, "export") || !ft_strcmp(temp, "unset") || \
		!ft_strcmp(temp, "env") || !ft_strcmp(temp, "exit"))
	{
		(*curr)->type = BUILTIN;
		ret = 1;
	}
	free(temp);
	return (ret);
}

static int	is_valid_redirect_arg(t_cmd_node **curr_cmd)
{
	enum e_cmd_type	type;

	type = (*curr_cmd)->type;
	if (!is_common_cmd(*curr_cmd))
	{
		if (is_common_cmd((*curr_cmd)->next))
		{
			*curr_cmd = (*curr_cmd)->next;
			(*curr_cmd)->type = REDIRARG;
		}
		else
			return 0; // 다음 그게 valid 하지 않다면?
			// return (parse_error(3));
	}
	// if (type == HEREDOC)
	// {
	// 	if (mini_heredoc(curr_cmd) == 0)
	// 		return (0);
	// }
	return (1);
}



void	check_cmd(t_cmd_list *cmd_list)
{
	int			i;
	int			flag;
	t_cmd_node	*curr;

	i = 0;
	while (i < cmd_list->size)
	{
		flag = 0;
		curr = cmd_list->cmd_heads[i];
		while (curr != NULL)
		{
			if (is_valid_redirect_arg(&curr) == 0)
				return ; // ㅇㅔ러처리
			if (!flag && curr->type == COMMON && is_builtin(&curr))
				tolower_str(curr->cmd);
			if (!flag && (curr->type == COMMON || curr->type == BUILTIN))
				flag = 1;
			curr = curr->next;
		}
		i++;
	}
}


void	transformation(t_cmd_list *cmd_list, t_token_node *token_head, char *line)
{
	int				i;
	t_token_node	*curr_token;

	// (void)line;
	i = 0;
	curr_token = token_head;
	init_cmd_size(cmd_list, token_head);
	while (i < cmd_list->size)
	{
		convert_token_to_command(&(cmd_list->cmd_heads[i]), &curr_token, line);
		i++;
		if (i < cmd_list->size && curr_token == NULL)
			exit_with_err("parseError", "", 5); // 
	}
	check_cmd(cmd_list);
}

void	parse(t_cmd_list *cmd_list)
{
	char			*line;
	t_token_node	*token_head;

	(void)cmd_list;
	ft_readline(&line);
	if (is_empty_line(line))
		return ;
	add_history(line);
	tokenization(&token_head, line);
	transformation(cmd_list, token_head, line);
}

