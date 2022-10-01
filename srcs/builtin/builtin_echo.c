/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:20:51 by hyuncho           #+#    #+#             */
/*   Updated: 2022/10/01 22:24:46 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	echo_print(t_cmd_node *node)
{
	while (node->next != NULL)
	{
		if (node->type == COMMON)
			printf("%s ", node->cmd);
		node = node->next;
	}
	printf("%s", node->cmd);
}

void	builtin_echo(t_cmd_node *node)
{
	int			option;

	option = false;
	node = node->next;
	if (node == NULL)
	{
		printf("\n");
		g_state.exit_status = 0;
		return ;
	}
	if (node->type == OPTION)
	{
		option = true;
		node = node->next;
	}
	g_state.exit_status = 0;
	if (node == NULL)
		return ;
	echo_print(node);
	if (option == false)
		printf("\n");
}
