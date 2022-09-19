/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2022/09/19 22:09:36 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_env(char **envp)
{
	t_env_node	*curr;
	t_env_node	*node;
	t_env_node	*temp_node;
	size_t		i;

	i = 0;
	curr = (t_env_node *)malloc(sizeof(t_env_node));
	g_state.env_head = &curr;
	temp_node = curr;
	curr->key = get_env_key(envp[i]);
	curr->value = get_env_value(envp[i]);
	curr->next = NULL;
	while (envp[++i])
	{
		node = create_env(envp[i]);
		if (node == NULL)
			return ;
		curr->next = node;
		curr = curr->next;
	}
	node = create_env(NULL);
	curr->next = node;
	while (temp_node->next != NULL)
	{
		printf("%s=%s\n", temp_node->key, temp_node->value);
		temp_node = temp_node->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	// t_cmd_line_list	*cmd_list;
	// char			*line;

	(void)argc;
	(void)argv;
	(void)envp;
	init_env(envp);

	return (0);
}

	/*
		1. 환경변수 처리


	*/

	/*
		lr parser
		Lalr parser

    	unset <- 환경변수 삭제
		export <- 환경변수 추가
		readline 함수 중에서 너무 빠르게 지랄하면 누수가 생긴다 <- 디펜스 잘 해봅시다
	*/