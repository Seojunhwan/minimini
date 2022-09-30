/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncho <hyuncho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:22:10 by hyuncho           #+#    #+#             */
/*   Updated: 2022/09/30 17:22:23 by hyuncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_redir_in(char *cmd)
{
	struct stat	file_info;

	if ((stat(cmd, &file_info) == -1))
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit(1);
	}
}

char	*have_redirect_in(t_cmd_node *node)
{
	t_cmd_node	*redirect_in;

	redirect_in = NULL;
	while (node != NULL)
	{
		if (node->type == REDIRIN)
		{
			do_redir_in(node->next->cmd);
			redirect_in = node;
		}
		node = node->next;
	}
	if (redirect_in)
		return (redirect_in->next->cmd);
	return (NULL);
}

void	redir_in(t_cmd_node *node)
{
	char	*file_name;
	int		fd;

	file_name = have_redirect_in(node);
	if (file_name != NULL)
	{
		fd = open(file_name, O_RDWR | O_CREAT, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("bash: ", STDERR_FILENO);
			ft_putstr_fd(file_name, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

static void	free_single_cmd_list(t_cmd_node *head)
{
	t_cmd_node	*curr;
	t_cmd_node	*temp;

	curr = head;
	while (curr != NULL)
	{
		temp = curr;
		if (curr->cmd != NULL)
			free(curr->cmd);
		curr = curr->next;
		free(temp);
	}
}

t_cmd_node	*remove_redirection_in_cmd(t_cmd_node *node)
{
	t_cmd_node	*new_list_head;
	t_cmd_node	*new_node;

	new_list_head = NULL;
	while (node != NULL)
	{
		if (node->type == COMMON || node->type == BUILTIN \
			|| node->type == OPTION)
		{
			new_node = cmd_dup(node);
			if (new_node == NULL || add_cmd(&new_list_head, new_node) == FALSE)
			{
				free_single_cmd_list(new_list_head);
				return (NULL);
			}
		}
		node = node->next;
	}
	return (new_list_head);
}
