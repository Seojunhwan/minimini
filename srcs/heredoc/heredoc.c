/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:45:27 by junseo            #+#    #+#             */
/*   Updated: 2022/09/29 20:56:13 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	write_dollar_heredoc(char *line, int start, int len, int fd)
{
	char	*name;
	char	*value;

	name = ft_substr(line, start, len); //$변수 를 substr하기($이후부터 자름)
	if (name == NULL)
	{
		write(fd, "\n", 1);
		return (FALSE);
	}
	value = get_env_via_key(name);
	if (value == NULL)
	{
		free(name);
		write(fd, "\n", 1);
		return (FALSE);
	}
	ft_putstr_fd(value, fd);
	free(name);
	free(value);
	return (TRUE);
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
		line[idx + 1] != ' ') //$이면서 변수가 존재하면
		{
			temp = ++idx;
			while (line[idx] != '\0' && !(ft_isspace(line[idx])) && \
			line[idx] != '$') //$$, 공백, null이 아니면 idx++하면서 $변수 길이 캐치
				idx++;
			if (write_dollar_heredoc(line, temp, idx - temp, fd) == FALSE)
				return (FALSE);
		}
		else
		{
			ft_putchar_fd(line[idx], fd);
			idx++;
		}
	}
	write(fd, "\n", 1);
	return (TRUE);
}

static int	heredoc_child(char *delimiter)
{
	int		fd;
	char	*line;

	set_heredoc_signal();
	line = NULL;
	fd = open("heredoc_file", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		parse_error(5); //printf("ERROR : Failed to open file\n");
		finish_heredoc(&line, fd, 1); //exit 1
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			move_heredoc_curser(fd);
		if (ft_strcmp(line, delimiter) == 0)
			finish_heredoc(&line, fd, 0);
		if (write_heredoc(fd, line) == FALSE)
			finish_heredoc(&line, fd, 1);
		free(line);
	}
	line = NULL;
	finish_heredoc(&line, fd, 0); //exit 0
}

int	do_heredoc(t_cmd_node **curr_cmd)
{
	pid_t	pid;
	int		status;
	int		ret;

	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		heredoc_child((*curr_cmd)->cmd);
	else
	{
		waitpid(pid, &status, 0);
		ret = status / 256;
		set_main_signal();
		if (ret == 130 || ret == 1)     //130, 1일경우에는 어떤경우?
		{
			g_state.exit_status = 1;
			remove_temp_file();
			return (FALSE);
		}
		(*curr_cmd)->prev->type = REDIRIN;      //HEREDOC->REDIRIN으로 전환하고 현재 cmd파일명으로 변경(heredoc_file)
		free((*curr_cmd)->cmd);
		(*curr_cmd)->cmd = ft_strdup("heredoc_file");
	}
	return (TRUE);
}
