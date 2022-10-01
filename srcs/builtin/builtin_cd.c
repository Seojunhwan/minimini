/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:20:47 by hyuncho           #+#    #+#             */
/*   Updated: 2022/10/01 17:43:04 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	return (current_dir);
}

void	home_dir(char *str)
{
	char	*tmp;
	char	*pwd_value;

	if (chdir(str) < 0)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	pwd_value = get_env_via_key("PWD");
	tmp = ft_strjoin("OLDPWD=", pwd_value);
	if (!modify_envp(tmp, "OLDPWD"))
		new_export(tmp);
	free(tmp);
	tmp = ft_strjoin("PWD=", str);
	if (!modify_envp(tmp, "PWD"))
		new_export(tmp);
	free(tmp);
}

void	old_dir(void)
{
	char	*old_pwd_value;
	char	*pwd_value;
	char	*tmp;

	old_pwd_value = ft_strdup(get_env_via_key("OLDPWD"));
	pwd_value = ft_strdup(get_env_via_key("PWD"));
	if (chdir(old_pwd_value) < 0)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(1);
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

static void	change_dir(char *str)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strdup(get_env_via_key("PWD"));
	if (chdir(str) < 0)
	{
		free(tmp);
		printf("cd: no such file or directory: %s\n", str);
		exit(1);
	}
	else
	{
		ret = ft_strjoin("PWD=", get_pwd());
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

void	builtin_cd(t_cmd_node *head)
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
		change_dir(curr_node->cmd);
}
