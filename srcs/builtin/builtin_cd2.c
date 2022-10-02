/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:20:50 by hyuncho           #+#    #+#             */
/*   Updated: 2022/10/03 05:08:01 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	home_dir_single(char *str)
{
	char	*tmp;
	char	*pwd_value;

	if (chdir(str) < 0)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		g_state.exit_status = 1;
		return ;
	}
	pwd_value = get_env_value_via_key("PWD");
	tmp = ft_strjoin("OLDPWD=", pwd_value);
	if (!modify_envp(tmp, "OLDPWD"))
		new_export(tmp);
	free(tmp);
	tmp = ft_strjoin("PWD=", str);
	if (!modify_envp(tmp, "PWD"))
		new_export(tmp);
	free(tmp);
}

static void	old_dir_single(void)
{
	char	*old_pwd_value;
	char	*pwd_value;
	char	*tmp;

	old_pwd_value = ft_strdup(get_env_value_via_key("OLDPWD"));
	pwd_value = ft_strdup(get_env_value_via_key("PWD"));
	if (chdir(old_pwd_value) < 0)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		g_state.exit_status = 1;
		return ;
	}
	tmp = ft_strjoin("PWD=", old_pwd_value);
	free(old_pwd_value);
	if (!modify_envp(tmp, "PWD"))
		new_export(tmp);
	free(tmp);
	tmp = ft_strjoin("OLDPWD=", pwd_value);
	free(pwd_value);
	if (!modify_envp(tmp, "OLDPWD"))
		new_export(tmp);
	free(tmp);
}

static void	change_dir_single(char *str)
{
	char	*tmp;
	char	*ret;	

	tmp = ft_strdup(get_env_value_via_key("PWD"));
	if (chdir(str) < 0)
	{
		free(tmp);
		printf("cd: no such file or directory: %s\n", str);
		g_state.exit_status = 1;
	}
	else
	{
		ret = ft_strjoin_with_free(ft_strdup("PWD="), get_pwd());
		if (!modify_envp(ret, "PWD"))
			new_export(ret);
		free(ret);
		ret = ft_strjoin("OLDPWD=", tmp);
		free(tmp);
		if (!modify_envp(ret, "OLDPWD"))
			new_export(ret);
		free(ret);
	}
}

void	builtin_cd_one_cmd(t_cmd_node *head)
{
	t_cmd_node	*curr_node;
	char		*str;

	curr_node = head->next;
	str = get_env_value_via_key("HOME");
	if (curr_node == NULL)
		home_dir_single(str);
	else if (ft_strcmp(curr_node->cmd, "~") == 0)
		home_dir_single(str);
	else if (ft_strcmp(curr_node->cmd, "-") == 0)
		old_dir_single();
	else
		change_dir_single(curr_node->cmd);
}
