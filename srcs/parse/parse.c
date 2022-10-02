/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:26:09 by junseo            #+#    #+#             */
/*   Updated: 2022/10/02 21:00:20 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_readline(char **line)
{
	*line = readline("\033[91;1mmini_mini_mini_shell$ \033[0m");
	if (!*line)
	{
		printf("exit\n");
		exit(0);
	}
}

static int	is_empty_line(char *line)
{
	while (*line != '\0')
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (1);
}

static void	release_line(char *line)
{
	if (line != NULL)
		free(line);
}

static void	release_token_list(t_token_node *token_head)
{
	t_token_node	*curr;
	t_token_node	*temp;

	curr = token_head;
	while (curr != NULL)
	{
		temp = curr;
		free(curr->token);
		curr = curr->next;
		free(temp);
	}
}

int	parse(t_cmd_list *cmd_list)
{
	char			*line;
	t_token_node	*token_head;

	ft_readline(&line);
	if (is_empty_line(line))
		return (false);
	add_history(line);
	if (tokenization(&token_head, line) == false)
	{
		release_line(line);
		release_token_list(token_head);
		return (false);
	}
	if (transformation(cmd_list, token_head, line) == false)
	{
		release_line(line);
		release_token_list(token_head);
		return (false);
	}
	release_line(line);
	release_token_list(token_head);
	return (true);
}
