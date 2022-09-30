/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncho <hyuncho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:20:51 by hyuncho           #+#    #+#             */
/*   Updated: 2022/09/30 17:21:17 by hyuncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	echo_print(t_cmd_node *node)
{
	while (node->next != NULL)
	{
		printf("%s ", node->cmd);
		node = node->next;
	}
	printf("%s", node->cmd);
}

void	builtin_echo(t_cmd_node *node)
{
	int			option;

	option = FALSE;
	node = node->next;
	if (node == NULL)
	{
		printf("\n");
		g_state.exit_status = 0;
		return ;
	}
	if (node->type == OPTION)
	{
		option = TRUE;
		node = node->next;
	}
	g_state.exit_status = 0;
	if (node == NULL)
		return ;
	echo_print(node);
	if (option == FALSE)
		printf("\n");
}
