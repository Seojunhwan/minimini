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

void	close_wait(int ***fd, pid_t **pid, int *status, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		close((*fd)[i][0]);
		close((*fd)[i][1]);
		i++;
	}
	i = 0;
	while (i < size)
	{
		waitpid((*pid)[i], &status[i], 0);
		if (!WIFSIGNALED(status[i]))
			g_state.exit_status = status[i] / 256;
		i++;
	}
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
