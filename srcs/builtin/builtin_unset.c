/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:21:04 by hyuncho           #+#    #+#             */
/*   Updated: 2022/10/01 16:42:33 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	builtin_unset_2(t_cmd_node *head, int flag)
{
	t_cmd_node	*curr_node;

	curr_node = head->next;
	while (curr_node != NULL)
	{
		if (is_right_form(curr_node->cmd) == false)
			flag = unset_error(curr_node->cmd);
		curr_node = curr_node->next;
	}
	return (flag);
}

static int	is_valid_env(char *str)
{
	int	i;

	i = -1;
	if (ft_isalpha(str[0]) == false && str[0] != '_')
		return (false);
	while (str[++i])
	{
		if (ft_isalnum(str[i]) == false && str[i] != '_')
			return (false);
	}
	return (true);
}

void	builtin_unset(t_cmd_node *head)
{
	int			flag;

	flag = builtin_unset_2(head, false);
	if (flag == true)
		exit(1);
}

void	remove_node_in_envp(t_env_node *node)
{
	t_env_node	*prev;

	if (node == NULL)
		return ;
	if (node == g_state.env_head)
		prev = NULL;
	else
	{
		prev = g_state.env_head;
		while (prev->next != node)
			prev = prev->next;
	}
	if (prev == NULL)
		g_state.env_head = node->next;
	else
		prev->next = node->next;
	free(node->key);
	free(node->value);
	free(node);
}

void	builtin_unset_one_cmd(t_cmd_node *head)
{
	t_cmd_node	*curr_node;
	t_env_node	*node_in_envp;

	curr_node = head->next;
	while (curr_node != NULL)
	{
		if (is_valid_env(curr_node->cmd) == true)
		{
			node_in_envp = is_in_envp(curr_node->cmd);
			if (node_in_envp != NULL)
				remove_node_in_envp(node_in_envp);
		}
		else if (is_right_form(curr_node->cmd) == false)
			unset_error_single(curr_node->cmd);
		curr_node = curr_node->next;
	}
}
