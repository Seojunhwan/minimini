/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:09:40 by junseo            #+#    #+#             */
/*   Updated: 2022/09/25 02:21:34 by junseo           ###   ########.fr       */
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