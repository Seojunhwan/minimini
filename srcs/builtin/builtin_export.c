#include "minishell.h"

void	export_wihtout_arg(t_cmd_node *head)
{
	int	i;

	if (head->next == NULL)
	{
		i = 0;
		while (g_state.envp[i])
			printf("declare -x %s\n", g_state.envp[i++]);
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

int	is_right_form(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == FALSE && str[0] != '_')
		return (FALSE);
	if (has_equal_sign(str) == TRUE)
	{
		while (str[i] != '=')
		{
			if (ft_isalnum(str[i]) == FALSE && str[i] != '_')
				return (FALSE);
			i++;
		}
		return (TRUE);
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == FALSE && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	builtin_export(t_cmd_node *node)
{
	// int			idx;
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
		// else if ((has_equal_sign(curr_node->cmd) == TRUE))
		// {
		// 	idx = is_in_envp(curr_node->cmd);
		// 	if (idx != -1)
		// 		modify_envp(curr_node->cmd, idx);
		// 	else
		// 		g_state.envp = new_export(curr_node->cmd);
		// }
		node = node->next;
	}
	if (flag == TRUE)
		exit(1);
}

int	is_in_envp(char *str)
{
	char	**split;
	int		i;

	i = -1;
	split = ft_split(str, '=');
	while (g_state.envp[++i])
	{
		if (ft_strncmp(g_state.envp[i], split[0], ft_strlen(split[0])) == 0)
		{
			free_split(split);
			return (i);
		}
	}
	free_split(split);
	return (-1);
}

char	**new_export(char *str)
{
	int		i;
	int		cnt;
	char	**ret;

	i = -1;
	cnt = 0;
	while (g_state.envp[++i])
		cnt++;
	ret = (char **)malloc(sizeof(char *) * (cnt + 2));
	if (!ret)
		exit(1);
	ret[cnt + 1] = NULL;
	i = -1;
	while (g_state.envp[++i])
		ret[i] = ft_strdup(g_state.envp[i]);
	ret[cnt] = ft_strdup(str);
	ret[cnt + 1] = NULL;
	free_split(g_state.envp);
	return (ret);
}

void	modify_envp(char *str, int loc)
{
	free(g_state.envp[loc]);
	g_state.envp[loc] = ft_strdup(str);
}

void	builtin_export_one_cmd(t_cmd_node *node)
{
	int			idx;

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
			idx = is_in_envp(node->cmd);
			if (idx != -1)
				modify_envp(node->cmd, idx);
			else
				g_state.envp = new_export(node->cmd);
		}
		node = node->next;
	}
}