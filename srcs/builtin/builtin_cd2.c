/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncho <hyuncho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:20:50 by hyuncho           #+#    #+#             */
/*   Updated: 2022/09/30 17:21:16 by hyuncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	change_dir_single(char *str)
{
	char	*tmp;
	char	*ret;

	tmp = get_env_via_key("PWD");
	if (chdir(str) < 0)
	{
		free(tmp);
		printf("cd: no such file or directory: %s\n", str);
		g_state.exit_status = 1;
	}
	else
	{
		ret = ft_strdup("PWD=");
		ret = ft_strjoin(ret, get_pwd());
		new_export(ret);
		free(ret);
		ret = ft_strdup("OLDPWD=");
		ret = ft_strjoin(ret, tmp);
		new_export(ret);
		free(ret);
		ret = 0;
	}
}

void	builtin_cd_one_cmd(t_cmd_node *head)
{
	t_cmd_node	*curr_node;
	char		*str;

	curr_node = head->next;
	str = get_env_via_key("HOME");
	if (curr_node == NULL)
		home_dir(str);
	else if (ft_strcmp(curr_node->cmd, "~") == 0)
		home_dir(str);
	else if (ft_strcmp(curr_node->cmd, "-") == 0)
		old_dir();
	else
		change_dir_single(curr_node->cmd);
}
