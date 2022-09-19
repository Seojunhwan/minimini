#include "minishell.h"

char	*get_path(char *key)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = -1;
	while (g_state.envp[++i])
	{
		if ((ft_strncmp(key, g_state.envp[i], ft_strlen(key)) == 0) \
		&& g_state.envp[i][ft_strlen(key)] == '=')
		{
			ret = ft_substr(g_state.envp[i], key_len(g_state.envp[i]) + \
			1, value_len(g_state.envp[i]));
			break ;
		}
	}
	return (ret);
}

void	path_error(char *str, char *cmd)
{
	if (str == NULL)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit(127);
	}
}

char	*is_valid_cmd_path(char *cmd)
{
	char		**split_path;
	int			i;
	char		*str;
	char		*str2;
	struct stat	s;

	str = get_path("PATH");
	path_error(str, cmd);
	split_path = ft_split(str, ':');
	free(str);
	i = -1;
	while (split_path[++i])
	{
		str = ft_strjoin(ft_strdup("/"), ft_strdup(cmd));
		str2 = ft_strjoin(ft_strdup(split_path[i]), str);
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

char *is_valid_cmd(char *cmd)
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