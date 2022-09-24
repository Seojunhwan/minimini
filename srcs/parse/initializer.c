/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:31:05 by junseo            #+#    #+#             */
/*   Updated: 2022/09/25 02:33:57 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_list *init_cmd()
{
	t_cmd_list	*new_cmd_list;

	new_cmd_list = (t_cmd_list *)ft_malloc(sizeof(t_cmd_list), 1);
	ft_memset(new_cmd_list, 0, sizeof(t_cmd_list));
	return (new_cmd_list);
}