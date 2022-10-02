/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 03:13:15 by junseo            #+#    #+#             */
/*   Updated: 2022/10/02 16:41:34 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tokenization(t_token_node **token_head, char *line)
{
	enum e_token_type	type;
	int					i;
	t_token_node		*new_node;

	i = 0;
	*token_head = NULL;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && ft_isspace(line[i]))
			i++;
		if (line[i] == '\0')
			return (true);
		type = get_token_type(line, i);
		if (type == TO_APPEND || type == TO_HEREDOC)
			i++;
		new_node = create_token_node(line, &i, type);
		if (!new_node)
			return (false);
		token_lstadd_back(token_head, &new_node);
	}
	return (true);
}
