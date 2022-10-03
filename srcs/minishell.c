/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2022/10/03 13:54:34 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	clear_cmd(t_cmd_list *cmd_line_list)
{
	t_cmd_node	*curr;
	t_cmd_node	*temp;
	int			idx;

	idx = 0;
	while (idx < cmd_line_list->size)
	{
		if (cmd_line_list->cmd_heads == NULL)
			break ;
		curr = cmd_line_list->cmd_heads[idx];
		while (curr != NULL)
		{
			temp = curr;
			if (curr->cmd != 0)
				free(curr->cmd);
			curr = curr->next;
			free(temp);
		}
		idx++;
	}
	free(cmd_line_list->cmd_heads);
	free(cmd_line_list);
	cmd_line_list = NULL;
}

static void	set_old_pwd(void)
{
	char		*old_pwd_value;

	old_pwd_value = get_env_value_via_key("OLDPWD");
	if (old_pwd_value == NULL)
		new_export(ft_strjoin_with_free(ft_strdup("OLDPWD="), get_pwd()));
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd_list	*cmd_list;

	if (argc != 1)
		exit_with_err("no no no no no argument!", NULL, 1);
	(void)argv;
	init_env(envp);
	set_old_pwd();
	set_signal(CUSTOM, CUSTOM);
	while (1)
	{
		disable_echoctl();
		cmd_list = init_cmd();
		if (parse(cmd_list) == false)
		{
			clear_cmd(cmd_list);
			continue ;
		}
		enable_echoctl();
		execute_cmd(cmd_list);
		clear_cmd(cmd_list);
		remove_temp_file();
	}
	return (0);
}
