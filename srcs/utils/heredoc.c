/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:35:51 by junseo            #+#    #+#             */
/*   Updated: 2022/09/29 19:41:38 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_temp_file(void)
{
	struct stat	s;

	if (stat("heredoc_file", &s) == 0)
		unlink("heredoc_file");
}

void	move_heredoc_curser(int fd)
{
	close(fd);
	ft_putstr_fd("\x1b[1A", 1);
	ft_putstr_fd("\033[2C", 1);
	exit(0);
}
