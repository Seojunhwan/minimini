/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2022/10/01 18:24:44 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	clear_cmd(t_cmd_list *cmd_line_list)
{
	t_cmd_node	*curr;
	t_cmd_node	*temp;
	int			idx;

	idx = 0;
	while (idx < cmd_line_list->size)
	{
		if (cmd_line_list->cmd_heads == NULL)
			break ;
		curr = cmd_line_list->cmd_heads[idx];
		while (curr != NULL)
		{
			temp = curr;
			if (curr->cmd != 0)
				free(curr->cmd);
			curr = curr->next;
			free(temp);
		}
		idx++;
	}
	free(cmd_line_list->cmd_heads);
	free(cmd_line_list);
	cmd_line_list = 0;
}

// void	test(t_cmd_list *p)
// {
// 	char	*table[] = {
// 				"COMMON",
// 				"REDIRIN",
// 				"REDIROUT",
// 				"HEREDOC",
// 				"APPEND",
// 				"REDIRARG",
// 				"BUILTIN",
// 				"OPTION"
// 	};
// 	// t_cmd_node **curr = p->cmd_heads;
// 	int i = 0;
// 	while (i < p->size)
// 	{
// 		t_cmd_node *save = p->cmd_heads[i];
// 		while (save)
// 		{
// 			printf("[%s], %s ", save->cmd, table[save->type]);
// 			save = save->next;
// 		}
// 		i++;
// 		printf("\n\n");
// 	}
// }


void	print_env(void)
{
	t_env_node *temp_node;

	temp_node = g_state.env_head;
	while (temp_node->next != NULL)
	{
		printf("%s=%s\n", temp_node->key, temp_node->value);
		temp_node = temp_node->next;
	}
}

static void	set_old_pwd(void)
{
	char		*old_pwd_value;

	old_pwd_value = get_env_via_key("OLDPWD");
	printf("%s\n", old_pwd_value);
	if (old_pwd_value == NULL)
		new_export(ft_strjoin_with_free(ft_strdup("OLDPWD="), get_pwd()));
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd_list	*cmd_list;

	(void)argc;
	(void)argv;
	init_env(envp);
	set_old_pwd();
	enable_signal();
	while (1)
	{
		disable_echoctl();
		cmd_list = init_cmd();
		if (parse(cmd_list) == false)
		{
			clear_cmd(cmd_list);
			continue ;
		}
		enable_echoctl();
		// test(cmd_list);
		execute_cmd(cmd_list);
		clear_cmd(cmd_list);
		remove_temp_file();
		//print_env();
	}
	return (0);
}

	/*
		1. argc 예외처리
		2. 환경변수 처리
			a. 환경변수 파싱
			b. 환경변수 PWD 확인 후 없으면 넣기

		3. readline 돌리기
			a. 입력 받기
			b. 토큰화하기
			c. 명령어 형태로 만들기
				A. 파이프 확인 후 미리 공간 할당
				B. 파이프 단위로 토큰 확인 후 명령어 형태로 변환
			

	*/

	/*
		lr parser
		Lalr parser

    	unset <- 환경변수 삭제
		export <- 환경변수 추가
		readline 함수 중에서 너무 빠르게 지랄하면 누수가 생긴다 <- 디펜스 잘 해봅시다
	*/