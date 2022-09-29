/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 01:04:25 by junseo            #+#    #+#             */
/*   Updated: 2022/09/25 01:57:44 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_env(char **envp)
{
	t_env_node	*curr;
	t_env_node	*new_node;
	t_env_node	*head;
	t_env_node	*temp_node; // 프린트용
	size_t		i;

	i = 0;
	head = (t_env_node *)malloc(sizeof(t_env_node));
	g_state.env_head = &head;
	curr = head;
	curr->key = extract_env_key(envp[i]);
	curr->value = extract_env_value(envp[i]);
	curr->next = NULL;
	while (envp[++i])
	{
		new_node = create_env_node(envp[i]);
		if (new_node == NULL)
			return ;
		curr->next = new_node;
		curr = curr->next;
	}
	new_node= create_env_node(NULL);

	// 프프린트용
	curr->next = new_node;
	temp_node = head;
	while (temp_node->next != NULL)
	{
		printf("%s=%s\n", temp_node->key, temp_node->value);
		temp_node = temp_node->next;
	}
}