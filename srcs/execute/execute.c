#include "../../includes/minishell.h"

void	execute_cmd(t_cmd_list *cmd_line_list)
{
	//cmd_line_list의 사이즈가 1인경우
		//execute_without_pipe();
	//pipe가 있는경우
		//execute_with_pipe();
	if (cmd_line_list->size == 1)
		execute_without_pipe(cmd_line_list);
	else
		execute_with_pipe(cmd_line_list);
}

void	execve_error(char *strerror, t_cmd_node *cmd_list)
{
	if (ft_strcmp(strerror, "Bad address") == 0)
	{
		ft_putstr_fd("bash : ", STDERR_FILENO);
		ft_putstr_fd(cmd_list->cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit(127);
	}
	else if (ft_strcmp(strerror, "Permission denied") == 0)
	{
		ft_putstr_fd("bash : ", STDERR_FILENO);
		ft_putstr_fd(cmd_list->cmd, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		exit(126);
	}
}