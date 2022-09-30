/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncho <hyuncho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:20:59 by hyuncho           #+#    #+#             */
/*   Updated: 2022/09/30 17:21:24 by hyuncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	export_wihtout_arg(t_cmd_node *head)
{
	t_env_node	*node;

	if (head->next == NULL)
	{
		node = g_state.env_head;
		while (node)
		{
			printf("declare -x %s=%s\n", node->key, node->value);
			node = node->next;
		}
	}
}

int	has_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	builtin_export(t_cmd_node *node)
{
	int			flag;

	flag = FALSE;
	export_wihtout_arg(node);
	node = node->next;
	while (node != NULL)
	{
		if (is_right_form(node->cmd) == FALSE)
		{
			flag = TRUE;
			ft_putstr_fd("bash : export : ", STDERR_FILENO);
			ft_putstr_fd(node->cmd, STDERR_FILENO);
			ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
		}
		node = node->next;
	}
	if (flag == TRUE)
		exit(1);
}

int	modify_envp(char *str, char *key)
{
	t_env_node	*curr;
	char		**split;

	curr = g_state.env_head;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			split = ft_split(str, '=');
			curr->value = ft_strdup(split[1]);
			free_split(split);
			return (TRUE);
		}
		curr = curr->next;
	}
	return (FALSE);
}

void	builtin_export_one_cmd(t_cmd_node *node)
{
	t_env_node	*node_in_envp;

	export_wihtout_arg(node);
	node = node->next;
	while (node != NULL)
	{
		if (is_right_form(node->cmd) == FALSE)
		{
			ft_putstr_fd("bash : export : ", STDERR_FILENO);
			ft_putstr_fd(node->cmd, STDERR_FILENO);
			ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
			g_state.exit_status = 1;
		}
		else if ((has_equal_sign(node->cmd) == TRUE))
		{
			node_in_envp = is_in_envp(node->cmd);
			if (node_in_envp != NULL)
				modify_envp(node->cmd, node_in_envp->key);
			else
				new_export(node->cmd);
		}
		node = node->next;
	}
}
