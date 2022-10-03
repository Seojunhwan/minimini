/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:20:47 by hyuncho           #+#    #+#             */
/*   Updated: 2022/10/03 17:34:01 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
		ft_putstr_fd("minishell : get_pwd() : can't search path\n", \
				STDERR_FILENO);
	return (current_dir);
}

void	home_dir(char *str)
{
	char	*tmp;
	char	*pwd_value;

	if (chdir(str) < 0)
		exit_with_err("chdir()", strerror(errno), 1);
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

void	old_dir(void)
{
	char	*old_pwd_value;
	char	*pwd_value;
	char	*tmp;

	old_pwd_value = ft_strdup(get_env_value_via_key("OLDPWD"));
	if (chdir(old_pwd_value) < 0)
	{
		free(old_pwd_value);
		exit_with_err("chdir", strerror(errno), 1);
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
}

static void	change_dir(char *str)
{
	char	*tmp;
	char	*ret;
	char	*curr_pwd;

	if (chdir(str) < 0)
		exit_with_err("cd: no such file or directory: ", str, 1);
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

void	builtin_cd(t_cmd_node *head)
{
	t_cmd_node	*curr_node;
	char		*str;

	curr_node = head->next;
	str = get_env_value_via_key("HOME");
	if (curr_node == NULL)
		home_dir(str);
	else if (ft_strcmp(curr_node->cmd, "~") == 0)
		home_dir(str);
	else if (ft_strcmp(curr_node->cmd, "-") == 0)
		old_dir();
	else
		change_dir(curr_node->cmd);
}
