/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:21:51 by junseo            #+#    #+#             */
/*   Updated: 2022/09/29 20:04:25 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_quote_cmd(t_cmd_node **cmd_head, t_token_node **token_head, char *line)
{
	t_token_node	*curr;

	curr = *token_head;
	if (need_join(curr, line, 1))
	{
		if (curr->type == QUOTE)
			join_cmd(cmd_head, curr->token);
		else
			join_dquote(cmd_head, &curr);
	}
	else
	{
		if (curr->type == QUOTE)
			new_quote(cmd_head, &curr);
		else
			new_dquote(cmd_head, &curr);
	}
	return ;
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
	return ;
}

void	convert_token_to_command(t_cmd_node **cmd_head, t_token_node **token_head, char *line)
{
	t_token_node	*curr;

	curr = *token_head;
	while (curr != NULL && curr->type != PIPE)
	{
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

int	transformation(t_cmd_list *cmd_list, t_token_node *token_head, char *line)
{
	int				i;
	t_token_node	*curr_token;

	i = 0;
	curr_token = token_head;
	init_cmd_size(cmd_list, token_head);
	while (i < cmd_list->size)
	{
		convert_token_to_command(&(cmd_list->cmd_heads[i]), &curr_token, line);
		i++;
		if (i < cmd_list->size && curr_token == NULL)
			parse_error(4);
	}
	return (command_validator(cmd_list));
}
