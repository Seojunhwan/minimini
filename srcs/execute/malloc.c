#include "../../includes/minishell.h"

static int	malloc_fd(int size, int ***fd)
{
	int	i;

	*fd = (int **)malloc(sizeof(int *) * size);
	if (*fd == NULL)
		return (FALSE);
	ft_memset(*fd, 0, sizeof(*fd));
	i = 0;
	while (i < size)
	{
		(*fd)[i] = (int *)malloc(sizeof(int) * 2);
		if ((*fd)[i] == NULL)
		{
			free_array((*fd), i);
			return (FALSE);
		}
		ft_memset((*fd)[i], 0, sizeof((*fd)[i]));
		i++;
	}
	return (TRUE);
}

static int	malloc_pid(int size, pid_t **pid)
{
	*pid = (pid_t *)malloc(sizeof(pid_t) * size);
	if (*pid == NULL)
		return (FALSE);
	ft_memset(*pid, 0, sizeof(*pid));
	return (TRUE);
}

static int	malloc_status(int size, int **status)
{
	*status = (int *)malloc(sizeof(int) * size);
	if (*status == NULL)
		return (FALSE);
	ft_memset(*status, 0, sizeof(*status));
	return (TRUE);
}

void	malloc_variables(int size, int ***fd, pid_t **pid, int **status)
{
	if (malloc_fd(size - 1, fd) != TRUE || malloc_pid \
	(size, pid) != TRUE || malloc_status(size, status) != TRUE)
	{
		g_state.exit_status = 1;
		exit(1);
	}
}
