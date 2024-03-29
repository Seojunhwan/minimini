/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:22:06 by hyuncho           #+#    #+#             */
/*   Updated: 2022/10/01 16:42:33 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	malloc_fd(int size, int ***fd)
{
	int	i;

	*fd = (int **)malloc(sizeof(int *) * size);
	if (*fd == NULL)
		return (false);
	ft_memset(*fd, 0, sizeof(*fd));
	i = 0;
	while (i < size)
	{
		(*fd)[i] = (int *)malloc(sizeof(int) * 2);
		if ((*fd)[i] == NULL)
		{
			free_array((*fd), i);
			return (false);
		}
		ft_memset((*fd)[i], 0, sizeof((*fd)[i]));
		i++;
	}
	return (true);
}

static int	malloc_pid(int size, pid_t **pid)
{
	*pid = (pid_t *)malloc(sizeof(pid_t) * size);
	if (*pid == NULL)
		return (false);
	ft_memset(*pid, 0, sizeof(*pid));
	return (true);
}

static int	malloc_status(int size, int **status)
{
	*status = (int *)malloc(sizeof(int) * size);
	if (*status == NULL)
		return (false);
	ft_memset(*status, 0, sizeof(*status));
	return (true);
}

void	malloc_variables(int size, int ***fd, pid_t **pid, int **status)
{
	if (malloc_fd(size - 1, fd) != true || malloc_pid \
	(size, pid) != true || malloc_status(size, status) != true)
	{
		g_state.exit_status = 1;
		exit(1);
	}
}

t_cmd_node	*cmd_dup(t_cmd_node *src_node)
{
	t_cmd_node	*new_node;

	new_node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	if (new_node == NULL)
		exit (1);
	ft_memset(new_node, 0, sizeof(t_cmd_node));
	new_node->cmd = ft_strdup(src_node->cmd);
	if (new_node->cmd == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = src_node->type;
	return (new_node);
}
