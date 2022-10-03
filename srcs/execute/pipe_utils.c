/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:22:08 by hyuncho           #+#    #+#             */
/*   Updated: 2022/10/03 14:52:51 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_process(int size, int ***fd)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		pipe((*fd)[i++]);
	}
}

void	wait_child(void)
{
	int		status;
	int		signo;

	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			signo = WTERMSIG(status);
			if (signo == SIGINT)
				ft_putstr_fd("\n", STDERR_FILENO);
			if (signo == SIGQUIT)
				ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
			g_state.exit_status = 128 + signo;
		}
		else
			g_state.exit_status = WEXITSTATUS(status);
	}
}

void	close_wait(int ***fd, pid_t **pid, int **status, int size)
{
	int	i;
	int	signo;

	set_signal(CUSTOM, CUSTOM);
	i = 0;
	while (i < size - 1)
	{
		close((*fd)[i][0]);
		close((*fd)[i][1]);
		i++;
	}
	wait_child();
	free_variables(size, fd, pid, status);
}

void	free_variables(int size, int ***fd, pid_t **pid, int **status)
{
	free_array(*fd, size - 1);
	free(*pid);
	pid = NULL;
	free(*status);
	status = NULL;
}

void	close_fd(int ***fd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close((*fd)[i][0]);
		close((*fd)[i][1]);
		i++;
	}
}
