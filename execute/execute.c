#include "minishell.h"

void	builtin_pwd()
{
	char	*curr_dir;

	curr_dir = getcwd(NULL, 0);
	if (curr_dir == NULL)
		printf("getcwd() cannot excute in fun_pwd\n");
	else
	{
		printf("%s\n", curr_dir);
		free(curr_dir);
	}
}

void	builtin_env()
{
	int	i;

	i = 0;
	while (g_state.envp[i])
		printf("%s\n", g_state.envp[i++]);
}

void	builtin_echo(t_cmd_node *node)
{
	int			option;

	option = FALSE;
	node = node->next;
	if (node == NULL)
	{
		printf("\n");
		g_state.exit_status = 0;
		return ;
	}
	if (node->type == OPTION)
	{
		option = TRUE;
		node = node->next;
	}
	g_state.exit_status = 0;
	if (node == NULL)
		return ;
	while (node->next != NULL)
	{
		printf("%s ", node->cmd);
		node = node->next;
	}
	printf("%s", node->cmd);
	if (option == FALSE)
		printf("\n");
}

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

void	redir_out(t_cmd_node *node)
{
	t_cmd_node	*redir_out_node;
	int			fd;

	redir_out_node = has_redir_out(node);
	if (redir_out_node != NULL)
	{
		if (redir_out_node->type == REDIROUT)
			fd = open(redir_out_node->next->cmd, O_RDWR, 0644);
		else
			fd = open(redir_out_node->next->cmd, O_RDWR | O_APPEND, 0644);
		if (fd < 0)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

t_cmd_node *remove_redirection_in_cmd(t_cmd_node *node)
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

char	*get_path(char *key)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = -1;
	while (g_state.envp[++i])
	{
		if ((ft_strncmp(key, g_state.envp[i], ft_strlen(key)) == 0) \
		&& g_state.envp[i][ft_strlen(key)] == '=')
		{
			ret = ft_substr(g_state.envp[i], key_len(g_state.envp[i]) + \
			1, value_len(g_state.envp[i]));
			break ;
		}
	}
	return (ret);
}

void	path_error(char *str, char *cmd)
{
	if (str == NULL)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit(127);
	}
}

char	*is_valid_cmd_path(char *cmd)
{
	char		**split_path;
	int			i;
	char		*str;
	char		*str2;
	struct stat	s;

	str = get_path("PATH");
	path_error(str, cmd);
	split_path = ft_split(str, ':');
	free(str);
	i = -1;
	while (split_path[++i])
	{
		str = ft_strjoin(ft_strdup("/"), ft_strdup(cmd));
		str2 = ft_strjoin(ft_strdup(split_path[i]), str);
		if (stat(str2, &s) == 0)
		{
			free_split(split_path);
			return (str2);
		}
		free(str2);
	}
	free_split(split_path);
	return (NULL);
}

char *is_valid_cmd(char *cmd)
{
	struct stat	s;
	int			i;
	char		*str;

	i = -1;
	str = NULL;
	if (stat(cmd, &s) == 0)
	{
		str = ft_strdup(cmd);
		return (str);
	}
	str = is_valid_cmd_path(cmd);
	return (str);
}

char	**cmd_change_to_array(t_cmd_node *node)
{
	t_cmd_node	*curr;
	char		**cmd_arr;
	int			cnt;
	int			i;

	i = 0;
	cnt = 0;
	curr = node;
	while (curr != NULL)
	{
		cnt++;
		curr = curr->next;
	}
	cmd_arr = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!cmd_arr)
		exit (1);
	curr = node;
	while (i < cnt)
	{
		cmd_arr[i] = ft_strdup(curr->cmd);
		curr = curr->next;
		i++;
	}
	cmd_arr[cnt] = NULL;
	return (cmd_arr);
}

static void	exec_one_cmd_without_pipe(t_cmd_node *node)
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

static void	execute_without_pipe(t_cmd_line_list *list)
{
	pid_t		pid;
	int			status;

	if(list->cmd_heads[0]->type == BUILTIN && have_redirect_in(list->cmd_heads[0]) == NULL && have_redirect_out(list->cmd_heads[0]) == NULL)// 빌트인이고 리다이렉션이 없는경우
		execute_one_builtin(list->cmd_heads[0]);
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




void	execute_cmd(t_cmd_line_list *cmd_line_list)
{
	//cmd_line_list의 사이즈가 1인경우
		//execute_without_pipe();
	//pipe가 있는경우
		//execute_with_pipe();
}




///////////////////////////////////////////////////////////////////////////////////
//파이프 있는 경우



void	execute_with_pipe(t_cmd_line_list *list)
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










///////////////////////////////////////////////////////////////////////////////////
//redirect

void	do_redir_in(char *cmd)
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

char*	have_redirect_in(t_cmd_node *node)
{
	t_cmd_node *redirect_in;

	redirect_in = NULL:
	while (node != NULL)
	{
		if (node->type == REDIRIN)
		{
			do_redir_in(node->cmd);
			redirect_in = node;
		}
		node = node->next;
	}
	if (redirect_in)
		return (redirect_in->next->cmd);
	return (redirect_in);
}

void	do_redir_out(char *cmd)
{
	int			fd;
	struct stat	s;

	if (stat(cmd, &s) == 0)
	{
		fd = open(cmd, O_RDWR | O_TRUNC, 0644);
		if (fd < 0)
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		close(fd);
	}
	else
	{
		fd = open(cmd, O_RDWR | O_CREAT, 0644);
		if (fd < 0)
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		close(fd);
	}
}

void	do_redir_append(char *cmd)
{
	int			fd;
	struct stat	s;

	if (stat(cmd, &s) != 0)
	{
		fd = open(cmd, O_RDWR | O_CREAT, 0644);
		if (fd < 0)
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		close(fd);
	}
}

char*	have_redirect_out(t_cmd_node *node)
{
	t_cmd_node *redirect_out;

	redirect_out = NULL:
	while (node != NULL)
	{
		if (node->type == REDIROUT)
		{
			do_redir_out(node->cmd);
			redirect_out = node;
		}
		else if (node->type == APPEND)
		{
			do_redir_append(node->cmd)
			redirect_out = node;
		}
		node = node->next;
	}
	if (redirect_out)
		return (redirect_out->next->cmd);
	return (redirect_out);
}