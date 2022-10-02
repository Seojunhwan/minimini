/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:50:39 by junseo            #+#    #+#             */
/*   Updated: 2022/10/02 17:14:32 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_node	*create_token_node(char	*line, int *i, \
	enum e_token_type type)
{
	t_token_node	*token;

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
		if (!token->token)
		{
			free(token);
			return (false);
		}
		(*i)++;
	}
	return (token);
}

void	token_lstadd_back(t_token_node **token_head, t_token_node **new_node)
{
	t_token_node	*last_node;

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
