#include "minishell.h"

void	execute_one_builtin(t_cmd_node	*node) //redirection 없는 경우
{
	if (ft_strcmp(node->cmd, "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp(node->cmd, "env") == 0)
		builtin_env();
	if (ft_strcmp(node->cmd, "echo") == 0)
		builtin_echo(node);
	if (ft_strcmp(node->cmd, "export") == 0)
		builtin_export_one_cmd(node);
	if (ft_strcmp(node->cmd, "unset") == 0)
		builtin_unset_one_cmd(node);
	if (ft_strcmp(node->cmd, "cd") == 0)
		builtin_cd_one_cmd(node);
	if (ft_strcmp(node->cmd, "exit") == 0)
		builtin_exit_one_cmd(node);
}

void	exe_builtin(t_cmd_node	*node)	//리다이렉션 있는경우
{
	if (ft_strcmp(node->cmd, "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp(node->cmd, "env") == 0)
		builtin_env();
	if (ft_strcmp(node->cmd, "echo") == 0)
		builtin_echo(node);
	if (ft_strcmp(node->cmd, "export") == 0)
		builtin_export(node);
	if (ft_strcmp(node->cmd, "unset") == 0)
		builtin_unset(node);
	if (ft_strcmp(node->cmd, "cd") == 0)
		builtin_cd(node);
	if (ft_strcmp(node->cmd, "exit") == 0)
		builtin_exit(node);
	exit(0);
}


static void	exec_one_cmd_without_pipe(t_cmd_node *node)
{
	//리다이렉션 체크
	//cmd_list 리다이렉션 리팩토링
	//builtin이면 빌트인 실행
		//execute_builtin
	//그냥 명령어 인경우 -> 명령어 stat와 환경변수로 체크하고 명령어문자열변환 -> execve
}

static void	execute_without_pipe(t_cmd_line_list *list)
{
	pid_t		pid;
	int			status;

	if(1)// 빌트인이고 리다이렉션이 없는경우
		;//execute_one_builtin
	else// 리다이렉션이 하나라도 있거나 빌트인이 아닌경우
	{
		//포크 -> 자식 프로세스, 부모프로세스 실행
		pid = fork();
		if (pid < -1)
			exit(1);
		if (pid == 0)
		{
			exec_one_cmd_without_pipe(node); //파이프 없이 명령어 실행
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


void	exe_with_pipe(t_cmd_line_list *list)
{
	int		idx;
	int		**fd;
	pid_t	*pid;
	int		*status;

	//할당
	//파이프 설정
	//연속적인 파이프
	
	//wait
	//free
	pipe_process(list->size, &fd);
	idx = -1;
	while (++idx < list->size)
	{
		pid[idx] = fork();
		if (pid[idx] < 0)
			exit(1);
		else if (pid[idx] == 0)
		{
			if (idx > 0)
				dup2(fd[idx - 1][0], STDIN_FILENO);
			if (idx < list->size - 1)
				dup2(fd[idx][1], STDOUT_FILENO);
			exe_single_cmd_with_pipe(list->cmd_heads[idx], &fd, list->size);
		}
	}
	close_wait(&fd, &pid, status, list->size);
	free_variables(list->size, &fd, &pid, &status);
}


void	execute_cmd(t_cmd_line_list *cmd_line_list)
{
	//cmd_line_list의 사이즈가 1인경우
		//execute_without_pipe();
	//pipe가 있는경우
		//execute_with_pipe();
}