/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:09:40 by junseo            #+#    #+#             */
/*   Updated: 2022/10/03 16:31:42 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const char	*g_errors[] = {
	"’(\") must be paired\n",
	"syntax error near unexpected token\n",
	"Invalid pipe\n",
	"Failed to open file\n",
};

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
	printf("\e[101;97;1mmini_mini_mini_shell:\e[0m ");
	if (option == 1 || option == 3)
		g_state.exit_status = 258;
	printf("%s\e[0m", g_errors[option]);
	return (false);
}
