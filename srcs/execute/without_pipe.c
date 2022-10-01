/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   without_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:22:14 by hyuncho           #+#    #+#             */
/*   Updated: 2022/10/01 19:04:31 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_one_cmd_without_pipe(t_cmd_node *node)
{
	t_cmd_node	*cmd_node;
	char		*path;
	char		**args;
	char		**envp_for_execve;


	redir_in(node);
	redir_out(node);
	cmd_node = remove_redirection_in_cmd(node);
	if (cmd_node->type == BUILTIN)
		execute_builtin(cmd_node);
	path = is_valid_cmd(cmd_node->cmd);
	args = cmd_change_to_array(cmd_node);
	envp_for_execve = set_envp();

	if (execve(path, args, envp_for_execve) == -1)
	{
		// int i = 0;
		// while (envp_for_execve[i])
		// {
		// 	printf("%s\n", envp_for_execve[i++]);
		// }
		free_split(envp_for_execve);
		execve_error(strerror(errno), cmd_node);
	}
	free_split(envp_for_execve);
}

void	execute_without_pipe(t_cmd_list *list)
{
	pid_t		pid;
	int			status;

	if (list->cmd_heads[0]->type == BUILTIN \
		&& have_redirect_in(list->cmd_heads[0]) == NULL \
			&& have_redirect_out(list->cmd_heads[0]) == NULL)
		execute_one_builtin(list->cmd_heads[0]);
	else
	{
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			exec_one_cmd_without_pipe(list->cmd_heads[0]);
			exit(1);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (!WIFSIGNALED(status))
				g_state.exit_status = status / 256;
		}
	}
}
