#include "minishell.h"

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

	redirect_out = NULL;
	while (node != NULL)
	{
		if (node->type == REDIROUT)
		{
			do_redir_out(node->cmd);
			redirect_out = node;
		}
		else if (node->type == APPEND)
		{
			do_redir_append(node->cmd);
			redirect_out = node;
		}
		node = node->next;
	}
	if (redirect_out)
		return (redirect_out->next->cmd);
	return (redirect_out);
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