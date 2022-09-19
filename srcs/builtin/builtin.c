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