/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:20:55 by hyuncho           #+#    #+#             */
/*   Updated: 2022/10/02 20:00:58 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(void)
{
	t_env_node	*node;

	node = g_state.env_head;
	while (node)
	{
		if (node->value != NULL)
			printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
}
