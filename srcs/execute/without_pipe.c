#include "minishell.h"

void	exec_one_cmd_without_pipe(t_cmd_node *node)
{
	//리다이렉션 체크
	//cmd_list 리다이렉션 리팩토링
	//builtin이면 빌트인 실행
		//execute_builtin
	//그냥 명령어 인경우 -> 명령어 stat와 환경변수로 체크하고 명령어문자열변환 -> execve

	/*
		redir_in();
		redir_out();
		cmd refactoring (only COMMON BUILTIN OPTION)
		if builtin -> execute builtin()
		arg1 = is valid cmd
		arg2 = cmd change to array
		execve(arg1, arg2);
	*/
	t_cmd_node *cmd_node;
	char *path;
	char *args;

	redir_in(node);
	redir_out(node);
	cmd_node = remove_redirection_in_cmd(node);
	if (cmd_node->type == BUILTIN)
		execute_builtin();
	path = is_valid_cmd(cmd_node->cmd);
	args = cmd_change_to_array(cmd_node);
	if (execve(path, args, g_state.envp) == -1)
		execve_error(strerror(errno), cmd_node);
}

void	execute_without_pipe(t_cmd_line_list *list)
{
	pid_t		pid;
	int			status;

	if(list->cmd_heads[0]->type == BUILTIN && have_redirect_in(list->cmd_heads[0]) == NULL && have_redirect_out(list->cmd_heads[0]) == NULL)// 빌트인이고 리다이렉션이 없는경우
		execute_one_builtin(list->cmd_heads[0]);
	else// 리다이렉션이 하나라도 있거나 빌트인이 아닌경우
	{
		//포크 -> 자식 프로세스, 부모프로세스 실행
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			exec_one_cmd_without_pipe(list->cmd_heads[0]); //파이프 없이 명령어 실행
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