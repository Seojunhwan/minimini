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