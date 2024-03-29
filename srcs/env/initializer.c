/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 01:04:25 by junseo            #+#    #+#             */
/*   Updated: 2022/10/02 17:18:33 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_env(char **envp)
{
	t_env_node	*curr;
	t_env_node	*new_node;
	size_t		i;
	char		*key;
	char		*value;

	i = 0;
	key = extract_env_key(envp[i]);
	value = extract_env_value(envp[i]);
	g_state.env_head = create_env_node(key, value);
	curr = g_state.env_head;
	while (envp[++i])
	{
		key = extract_env_key(envp[i]);
		value = extract_env_value(envp[i]);
		new_node = create_env_node(key, value);
		curr->next = new_node;
		curr = curr->next;
	}
}
