/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:25:31 by junseo            #+#    #+#             */
/*   Updated: 2022/09/29 19:03:18 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	dquote_dollar(char **new_str, char *key)
{
	char	*value;

	if (ft_strcmp(key, "?") == 0)
	{
		*new_str = ft_strjoin_with_free(*new_str, ft_itoa(g_state.exit_status));
		return ;
	}
	value = ft_strdup(get_env_via_key(key));
	if (value == NULL)
		return ;
	*new_str = ft_strjoin_with_free(*new_str, value);
}
