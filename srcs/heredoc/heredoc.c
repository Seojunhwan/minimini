/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:45:27 by junseo            #+#    #+#             */
/*   Updated: 2022/10/02 22:01:37 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	write_dollar_heredoc(char *line, int start, int len, int fd)
{
	char	*name;
	char	*value;

	name = ft_substr(line, start, len);
	if (name == NULL)
	{
		write(fd, "\n", 1);
		return (false);
	}
	value = get_env_via_key(name);
	if (value == NULL)
	{
		free(name);
		write(fd, "\n", 1);
		return (false);
	}
	ft_putstr_fd(value, fd);
	free(name);
	return (true);
}

static void	finish_heredoc(char **line, int fd, int end_status)
{
	if (*line != NULL)
		free(*line);
	if (fd >= 0)
		close(fd);
	exit(end_status);
}

static int	write_heredoc(int fd, char *line)
{
	int		idx;
	int		temp;

	idx = 0;
	while (line[idx] != '\0')
	{
		if (line[idx] == '$' && line[idx + 1] != '\0' && \
		line[idx + 1] != ' ')
		{
			temp = ++idx;
			while (line[idx] != '\0' && !(ft_isspace(line[idx])) && \
			line[idx] != '$')
				idx++;
			if (write_dollar_heredoc(line, temp, idx - temp, fd) == false)
				return (false);
		}
		else
		{
			ft_putchar_fd(line[idx], fd);
			idx++;
		}
	}
	write(fd, "\n", 1);
	return (true);
}

static int	get_file_index(int flag)
{
	static int	index;

	if (flag == 1)
	{
		index = 0;
		return (index);
	}
	index++;
	return (index);
}

void	remove_temp_file(void)
{
	struct stat	s;
	int			i;
	int			n;
	char		*file_name;

	i = 1;
	n = get_file_index(0);
	while (i < n)
	{
		file_name = ft_strjoin_with_free(ft_strdup("heredoc_file"), ft_itoa(i));
		if (stat(file_name, &s) == 0)
			unlink(file_name);
		free(file_name);
		i++;
	}
	get_file_index(1);
}

static int	heredoc_child(char *delimiter, int index)
{
	int		fd;
	char	*line;
	char	*temp_name;

	enable_heredoc_signal();
	line = NULL;
	temp_name = ft_strjoin_with_free(ft_strdup("heredoc_file"), ft_itoa(index));
	fd = open(temp_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		free(temp_name);
		parse_error(5);
		finish_heredoc(&line, fd, 1);
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			move_heredoc_curser(fd);
		if (ft_strcmp(line, delimiter) == 0)
			finish_heredoc(&line, fd, 0);
		if (write_heredoc(fd, line) == false)
			finish_heredoc(&line, fd, 1);
		free(line);
	}
	line = NULL;
	free(temp_name);
	finish_heredoc(&line, fd, 0);
}

int	do_heredoc(t_cmd_node **curr_cmd)
{
	pid_t		pid;
	int			status;
	int			ret;
	int			heredoc_index;

	signal(SIGQUIT, SIG_IGN);
	heredoc_index = get_file_index(0);
	pid = fork();
	if (pid == 0)
		heredoc_child((*curr_cmd)->cmd, heredoc_index);
	else
	{
		waitpid(pid, &status, 0);
		ret = status / 256;
		enable_signal();
		if (ret == 130 || ret == 1)
		{
			g_state.exit_status = 1;
			remove_temp_file();
			return (false);
		}
		(*curr_cmd)->prev->type = REDIRIN;
		free((*curr_cmd)->cmd);
		(*curr_cmd)->cmd = ft_strjoin_with_free(\
		ft_strdup("heredoc_file"), ft_itoa(heredoc_index));
	}
	return (true);
}
