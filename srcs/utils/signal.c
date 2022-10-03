/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:43:20 by junseo            #+#    #+#             */
/*   Updated: 2022/10/03 13:53:59 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signal(enum e_sig_type sig_int, enum e_sig_type sig_quit)
{
	if (sig_int == IGNORE)
		signal(SIGINT, SIG_IGN);
	if (sig_int == DEFAULT)
		signal(SIGINT, SIG_DFL);
	if (sig_int == CUSTOM)
		signal(SIGINT, signal_handler);
	if (sig_quit == IGNORE)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	if (sig_quit == CUSTOM)
		signal(SIGQUIT, signal_handler);
}
