/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2022/09/25 02:35:20 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_cmd_list	*cmd_list;

	(void)argc;
	(void)argv;

	init_env(envp);
	// if (get_env_via_key("OLDPWD") == NULL)
		// 환경변수 추가하기
	while (1)
	{
		disable_echoctl();
		cmd_list = init_cmd();
		parse(&cmd_list);
		enable_echoctl();
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