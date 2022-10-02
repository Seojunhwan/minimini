/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:40:22 by junseo            #+#    #+#             */
/*   Updated: 2022/10/02 16:41:06 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	make_new_dollar_string(int *i, t_token_node **curr, char **new_str)
{
	char	*temp_str;
	int		start;

	start = ++(*i);
	while ((*curr)->token[*i] != '\0' && (*curr)->token[*i] != '$' && \
		!ft_isspace((*curr)->token[*i]) && (*curr)->token[*i] != '\'')
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
