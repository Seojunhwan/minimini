/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 03:13:15 by junseo            #+#    #+#             */
/*   Updated: 2022/09/29 16:56:21 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

enum e_token_type get_token_type(char *line, int i)
{
	if (line[i] == '|')
		return (PIPE);
	else if (line[i] == '$') 
		return (DOLLAR);
	else if (line[i] == '"') 
		return (DQUOTE);
	else if (line[i] == '\'') 
		return (QUOTE);
	else if (line[i] == '<') 
	{
		if (line[i + 1] != '\0' && line[i + 1] == '<')
			return (TO_HEREDOC);
		return (TO_REDIRIN);
	}
	else if (line[i] == '>')
	{
		if (line[i + 1] != '\0' && line[i + 1] == '>')
			return (TO_APPEND);
		return (TO_REDIROUT);
	}
	return (TO_COMMON);
}

char	*extract_common_token_from_line(char *line, int *i)
{
	char	*token_str;
	int		start;

	start = *i;
	while (line[*i] != '\0' && !ft_isspace(line[*i]) && get_token_type(line, *i) == COMMON)
		(*i)++;
	token_str = ft_substr(line, start, *i - start);
	return (token_str);
}

char	*extract_quote_token_from_line(char *line, int *i)
{
	char	quote;
	char	*token_str;
	int		start;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] != '\0' && line[*i] != quote)
		(*i)++;
	token_str = ft_substr(line, start, *i - start);
	return (token_str);
}

static const	char *g_tables[] = {
	"",
	"<",
	">",
	"<<",
	">>",
	"|",
	"$"
};

char	*extract_special_token_from_line(char *line, int *i, enum e_token_type type)
{
	char	*token_str;

	if (type == DQUOTE || type == QUOTE)
		token_str = extract_quote_token_from_line(line, i);
	else
		token_str = ft_strdup(g_tables[type]);
	// else if (type == TO_REDIRIN)
	// 	token_str = ft_strdup("<");
	// else if (type == TO_REDIROUT)
	// 	token_str = ft_strdup(">");
	// else if (type == TO_HEREDOC)
	// 	token_str = ft_strdup("<<");
	// else if (type == TO_APPEND)
	// 	token_str = ft_strdup(">>");
	// else if (type == PIPE)
	// 	token_str = ft_strdup("|");
	// else if (type == DOLLAR)
	// 	token_str = ft_strdup("$");
	// else
	// 	token_str = ft_strdup("");
	return (token_str);
}



t_token_node	*create_token_node(char	*line, int *i, enum e_token_type type)
{
	t_token_node	*token;

	// char const	*types[] = {
	// 	"TO_COMMON",
	// 	"TO_REDIRIN",
	// 	"TO_REDIROUT",
	// 	"TO_HEREDOC",
	// 	"TO_APPEND",
	// 	"PIPE",
	// 	"DQUOTE",
	// 	"QUOTE",
	// 	"DOLLAR"
	// };
	token = (t_token_node *)ft_malloc(sizeof(t_token_node), 1);
	token->type = type;
	token->idx = *i;
	token->prev = NULL;
	token->next = NULL;
	if (type == TO_COMMON)
		token->token = extract_common_token_from_line(line, i);
	else
	{
		token->token = extract_special_token_from_line(line, i, type);
		(*i)++;
	}
	// printf("--------token--------\ntoken : %s | index : %d | type : %s\n\n", token->token, token->idx, types[token->type]);
	return (token);
}

void	token_lstadd_back(t_token_node **token_head, t_token_node **new_node)
{
	t_token_node *last_node;

	if (*token_head == NULL)
		*token_head = *new_node;
	else
	{
		last_node = *token_head;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = *new_node;
		(*new_node)->prev = last_node;
	}
}

// static const	char *g_types[] = {
// 			"TO_COMMON",
// 			"TO_REDIRIN",
// 			"TO_REDIROUT",
// 			"TO_HEREDOC",
// 			"TO_APPEND",
// 			"PIPE",
// 			"DQUOTE",
// 			"QUOTE",
// 			"DOLLAR"
// };

void	tokenization(t_token_node **token_head, char *line)
{
	enum e_token_type	type;
	int					i;
	t_token_node		*new_node;
	// t_token_node		*temp;
	i = 0;
	*token_head = NULL;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && ft_isspace(line[i]))
			i++;
		if (line[i] == '\0')
			return ;
		type = get_token_type(line, i);
		if (type == TO_APPEND || type == TO_HEREDOC)
			i++;
		new_node = create_token_node(line, &i, type);
		// printf("\n------------------------------------\ntoken : %s | index : %d | type : %s\n\n", new_node->token, new_node->idx, types[new_node->type]);
		token_lstadd_back(token_head, &new_node);
	}
	// temp = *token_head; // 프린트용
	// while (temp != NULL)
	// {
	// 	printf("------------------------------------\ntoken : %s | index : %d | type : %s\n------------------------------------\n\n", temp->token, temp->idx, types[temp->type]);
	// 	if (temp->next == NULL)
	// 		break;
	// 	temp = temp->next;
	// }
}