/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:37:08 by junseo            #+#    #+#             */
/*   Updated: 2022/10/03 20:39:01 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	need_join(t_token_node *curr_token, char *line, int option)
{
	char	c;

	if (curr_token->idx - 1 > 0)
		c = line[curr_token->idx - 1];
	else
		c = '\0';
	if (option == 1)
		return (c != '\0' && !(c == ' ' || (c >= 9 && c <= 13)));
	else if (option == 2)
		return (c != '\0' && (c == '\'' || c == '"' || \
			!(c == ' ' || c == '|' || (c >= 9 && c <= 13))));
	else
		return (c != '\0' && (c == '\'' || c == '"'));
}

void	join_cmd(t_cmd_node **cmd_head, char *cmd)
{
	t_cmd_node		*last_cmd;
	char			*temp;

	last_cmd = *cmd_head;
	while (last_cmd->next != NULL)
		last_cmd = last_cmd->next;
	temp = last_cmd->cmd;
	last_cmd->cmd = ft_strjoin(temp, cmd);
	free(temp);
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
		last_cmd = last_cmd->next;
	last_cmd->cmd = ft_strjoin_with_free(last_cmd->cmd, new_str);
}
