/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:22:03 by hyuncho           #+#    #+#             */
/*   Updated: 2022/10/03 05:08:01 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	path_error(char *str, char *cmd)
{
	if (str == NULL)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit(127);
	}
}

static char	*is_valid_cmd_path(char *cmd)
{
	char		**split_path;
	int			i;
	char		*str;
	char		*str2;
	struct stat	s;

	str = ft_strdup(get_env_value_via_key("PATH"));
	path_error(str, cmd);
	split_path = ft_split(str, ':');
	free(str);
	i = -1;
	while (split_path[++i])
	{
		str = ft_strjoin_with_free(ft_strdup("/"), ft_strdup(cmd));
		str2 = ft_strjoin_with_free(ft_strdup(split_path[i]), str);
		if (stat(str2, &s) == 0)
		{
			free_split(split_path);
			return (str2);
		}
		free(str2);
	}
	free_split(split_path);
	return (NULL);
}

char	*is_valid_cmd(char *cmd)
{
	struct stat	s;
	int			i;
	char		*str;

	i = -1;
	str = NULL;
	if (stat(cmd, &s) == 0)
	{
		str = ft_strdup(cmd);
		return (str);
	}
	str = is_valid_cmd_path(cmd);
	return (str);
}

char	**cmd_change_to_array(t_cmd_node *node)
{
	t_cmd_node	*curr;
	char		**cmd_arr;
	int			cnt;
	int			i;

	i = 0;
	cnt = 0;
	curr = node;
	while (curr != NULL)
	{
		cnt++;
		curr = curr->next;
	}
	cmd_arr = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!cmd_arr)
		exit (1);
	curr = node;
	while (i < cnt)
	{
		cmd_arr[i] = ft_strdup(curr->cmd);
		curr = curr->next;
		i++;
	}
	cmd_arr[cnt] = NULL;
	return (cmd_arr);
}

int	add_cmd(t_cmd_node **cmd_head, t_cmd_node *new_node)
{
	t_cmd_node	*last_node;

	if (*cmd_head == 0)
		*cmd_head = new_node;
	else
	{
		last_node = *cmd_head;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	return (true);
}
