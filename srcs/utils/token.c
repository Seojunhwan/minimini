/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:51:08 by junseo            #+#    #+#             */
/*   Updated: 2022/10/03 02:40:28 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const char	*g_tables[] = {
	"",
	"<",
	">",
	"<<",
	">>",
	"|",
	"$"
};

enum e_token_type	get_token_type(char *line, int i)
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
	while (line[*i] != '\0' && !ft_isspace(line[*i]) \
			&& get_token_type(line, *i) == COMMON)
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
	if (line[*i] == '\0')
	{
		parse_error(0);
		return (false);
	}
	token_str = ft_substr(line, start, *i - start);
	return (token_str);
}

char	*extract_special_token_from_line(char *line, int *i, \
		enum e_token_type type)
{
	char	*token_str;

	if (type == DQUOTE || type == QUOTE)
		token_str = extract_quote_token_from_line(line, i);
	else
		token_str = ft_strdup(g_tables[type]);
	return (token_str);
}
