/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:20:50 by hyuncho           #+#    #+#             */
/*   Updated: 2022/10/03 17:33:30 by junseo           ###   ########.fr       */
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
	if (chdir(old_pwd_value) < 0)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		g_state.exit_status = 1;
		free(old_pwd_value);
		return ;
	}
	pwd_value = ft_strdup(get_env_value_via_key("PWD"));
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
	if (get_env_value_via_key("PWD") != NULL)
		printf("%s\n", get_env_value_via_key("PWD"));
}

static void	change_dir_single(char *str)
{
	char	*tmp;
	char	*ret;
	char	*curr_pwd;

	if (chdir(str) < 0)
	{
		printf("cd: no such file or directory: %s\n", str);
		g_state.exit_status = 1;
	}
	else
	{
		curr_pwd = get_pwd();
		if (curr_pwd == NULL)
			return ;
		tmp = ft_strdup(get_env_value_via_key("PWD"));
		ret = ft_strjoin_with_free(ft_strdup("PWD="), curr_pwd);
		if (!modify_envp(ret, "PWD"))
			new_export(ret);
		free(ret);
		ret = ft_strjoin_with_free(ft_strdup("OLDPWD="), tmp);
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
