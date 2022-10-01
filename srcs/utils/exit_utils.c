/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:09:40 by junseo            #+#    #+#             */
/*   Updated: 2022/10/01 16:42:11 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_with_err(char *msg, char *msg2, int error_no)
{
	ft_putstr_fd("minishell :", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (msg2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	exit(error_no);
}

int	parse_error(int option)
{
	g_state.exit_status = 1;
	if (option == 1)
	{
		g_state.exit_status = 258;
		printf("ERROR : ’(\") must be paired\n");
	}
	else if (option == 2)
		printf("ERROR : Memory allocation failed\n");
	else if (option == 3)
	{
		g_state.exit_status = 258;
		printf("syntax error near unexpected token\n");
	}
	else if (option == 4)
	{
		printf("ERROR : Invaild pipe\n");
	}
	else if (option == 5)
	{
		printf("ERROR : Failed to open file\n");
	}
	return (false);
}