/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:34:56 by junseo            #+#    #+#             */
/*   Updated: 2022/09/29 19:04:29 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
