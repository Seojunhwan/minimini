/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:31:05 by junseo            #+#    #+#             */
/*   Updated: 2022/09/29 18:32:49 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_list	*init_cmd(void)
{
	t_cmd_list	*new_cmd_list;

	new_cmd_list = (t_cmd_list *)ft_malloc(sizeof(t_cmd_list), 1);
	ft_memset(new_cmd_list, 0, sizeof(t_cmd_list));
	return (new_cmd_list);
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
