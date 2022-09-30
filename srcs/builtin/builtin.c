/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncho <hyuncho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:23:53 by hyuncho           #+#    #+#             */
/*   Updated: 2022/09/30 17:23:54 by hyuncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_one_builtin(t_cmd_node	*node)
{
	if (ft_strcmp(node->cmd, "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp(node->cmd, "env") == 0)
		builtin_env();
	if (ft_strcmp(node->cmd, "echo") == 0)
		builtin_echo(node);
	if (ft_strcmp(node->cmd, "export") == 0)
		builtin_export_one_cmd(node);
	if (ft_strcmp(node->cmd, "unset") == 0)
		builtin_unset_one_cmd(node);
	if (ft_strcmp(node->cmd, "cd") == 0)
		builtin_cd_one_cmd(node);
	if (ft_strcmp(node->cmd, "exit") == 0)
		builtin_exit_one_cmd(node);
}

void	execute_builtin(t_cmd_node	*node)
{
	if (ft_strcmp(node->cmd, "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp(node->cmd, "env") == 0)
		builtin_env();
	if (ft_strcmp(node->cmd, "echo") == 0)
		builtin_echo(node);
	if (ft_strcmp(node->cmd, "export") == 0)
		builtin_export(node);
	if (ft_strcmp(node->cmd, "unset") == 0)
		builtin_unset(node);
	if (ft_strcmp(node->cmd, "cd") == 0)
		builtin_cd(node);
	if (ft_strcmp(node->cmd, "exit") == 0)
		builtin_exit(node);
	exit(0);
}
