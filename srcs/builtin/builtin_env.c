/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncho <hyuncho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:20:55 by hyuncho           #+#    #+#             */
/*   Updated: 2022/09/30 17:21:18 by hyuncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(void)
{
	t_env_node	*node;

	node = g_state.env_head;
	while (node)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
}
