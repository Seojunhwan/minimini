#include "minishell.h"

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
	int			loc;

	curr_node = head->next;
	while (curr_node != NULL)
	{
		if (is_right_form(curr_node->cmd) == FALSE)
			flag = unset_error(curr_node->cmd);
		curr_node = curr_node->next;
	}
	return (flag);
}

void	builtin_unset(t_cmd_node *head)
{
	int			flag;

	flag = builtin_unset_2(head, FALSE);
	if (flag == TRUE)
		exit(1);
}

void	builtin_unset_single_cmd(t_cmd_node *head)
{
	int			loc;
	t_cmd_node	*curr_node;

	curr_node = head->next;
	while (curr_node != NULL)
	{
		if (is_valid_env(curr_node->cmd) == TRUE)
		{
			loc = is_str_in_envp(curr_node->cmd);
			if (loc != FALSE)
			{
				while (loc < envp_cnt() - 1)
				{
					free(g_state.envp[loc]);
					g_state.envp[loc] = ft_strdup(g_state.envp[loc + 1]);
					loc++;
				}
				free(g_state.envp[envp_cnt() - 1]);
				g_state.envp[envp_cnt() - 1] = NULL;
			}
		}
		else if (is_right_form(curr_node->cmd) == FALSE)
			unset_error_single(curr_node->cmd);
		curr_node = curr_node->next;
	}
}