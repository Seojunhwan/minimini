#include "../../includes/minishell.h"

static void	export_wihtout_arg(t_cmd_node *head)
{
	t_env_node	*node;

	if (head->next == NULL)
	{
		node = g_state.env_head;
		while (node)
		{
			printf("declare -x %s=%s\n",node->key, node->value);
			node = node->next;
		}
	}
}

static int	has_equal_sign(char *str)
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

t_env_node	*is_in_envp(char *str)
{
	t_env_node	*node;
	char		**split;

	node = g_state.env_head;
	split = ft_split(str, '=');
	while (node)
	{
		if (ft_strncmp(node->key, split[0], ft_strlen(split[0])) == 0)
		{
			free_split(split);
			return (node);
		}
		node = node->next;
	}
	free_split(split);
	return (NULL);
}

void	new_export(char *str)
{
	t_env_node	*new_node;
	t_env_node	*curr;
	char		**split;

	if (has_equal_sign(str))
	{
		split = ft_split(str, '=');
		new_node = create_env_node(split[0], split[1]);
	}
	else
		new_node = create_env_node(str, NULL);
	curr = g_state.env_head;
	if (curr == NULL)
	{
		g_state.env_head = new_node;
		return ;
	}
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
}

static void	modify_envp(char *str, char *key)
{
	t_env_node	*curr;
	char		**split;

	curr = g_state.env_head;
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			split = ft_split(str, '=');
			curr->value = ft_strdup(split[1]);
			free_split(split);
			return ;
		}
		curr = curr->next;
	}
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