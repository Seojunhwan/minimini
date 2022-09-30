#include "../../includes/minishell.h"

static int	unset_error(char *cmd)
{
	ft_putstr_fd("bash : unset : ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	return (TRUE);
}

static int	builtin_unset_2(t_cmd_node *head, int flag)
{
	t_cmd_node	*curr_node;

	curr_node = head->next;
	while (curr_node != NULL)
	{
		if (is_right_form(curr_node->cmd) == FALSE)
			flag = unset_error(curr_node->cmd);
		curr_node = curr_node->next;
	}
	return (flag);
}

static int	is_valid_env(char *str)
{
	int	i;

	i = -1;
	if (ft_isalpha(str[0]) == FALSE && str[0] != '_')
		return (FALSE);
	while (str[++i])
	{
		if (ft_isalnum(str[i]) == FALSE && str[i] != '_')
			return (FALSE);
	}
	return (TRUE);
}

void	builtin_unset(t_cmd_node *head)
{
	int			flag;

	flag = builtin_unset_2(head, FALSE);
	if (flag == TRUE)
		exit(1);
}

void	remove_node_in_envp(t_env_node *node)
{
	t_env_node	*prev;
	
	if (node == NULL)
		return ;
	if (node == g_state.env_head)
		prev = NULL;
	else
	{
		prev = g_state.env_head;
		while (prev->next != node)
			prev = prev->next;
	}
	if (prev == NULL)
		g_state.env_head = node->next;
	else
		prev->next = node->next;
	free(node->key);
	free(node->value);
	free(node);
}

static void	unset_error_single(char *cmd)
{
	ft_putstr_fd("bash : unset : ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	g_state.exit_status = 1;
}

void	builtin_unset_one_cmd(t_cmd_node *head)
{
	t_cmd_node	*curr_node;
	t_env_node	*node_in_envp;

	curr_node = head->next;
	while (curr_node != NULL)
	{
		if (is_valid_env(curr_node->cmd) == TRUE)
		{
			node_in_envp = is_in_envp(curr_node->cmd);
			if (node_in_envp != NULL)
				remove_node_in_envp(node_in_envp);
		}
		else if (is_right_form(curr_node->cmd) == FALSE)
			unset_error_single(curr_node->cmd);
		curr_node = curr_node->next;
	}
}