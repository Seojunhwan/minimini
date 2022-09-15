/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:03:17 by junseo            #+#    #+#             */
/*   Updated: 2022/09/15 15:14:05 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	char	*line;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("hihi : ");
		printf("%s\n", line);
	}
	return (0);
}

