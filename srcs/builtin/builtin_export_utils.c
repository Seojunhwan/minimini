/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncho <hyuncho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:20:59 by hyuncho           #+#    #+#             */
/*   Updated: 2022/09/30 17:21:24 by hyuncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_node	*is_in_envp(char *str)
{
	t_env_node	*node;
	char		**split;

	node = g_state.env_head;
	split = ft_split(str, '=');
	while (node)
	{
		if (ft_strncmp(node->key, split[0], ft_strlen(split[0])) == 0)
		{
			free_split(split);
			return (node);
		}
		node = node->next;
	}
	free_split(split);
	return (NULL);
}

void	new_export(char *str)
{
	t_env_node	*new_node;
	t_env_node	*curr;
	char		**split;

	if (has_equal_sign(str))
	{
		split = ft_split(str, '=');
		new_node = create_env_node(split[0], split[1]);
	}
	else
		new_node = create_env_node(str, NULL);
	curr = g_state.env_head;
	if (curr == NULL)
	{
		g_state.env_head = new_node;
		return ;
	}
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
}

int	is_right_form(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == FALSE && str[0] != '_')
		return (FALSE);
	if (has_equal_sign(str) == TRUE)
	{
		while (str[i] != '=')
		{
			if (ft_isalnum(str[i]) == FALSE && str[i] != '_')
				return (FALSE);
			i++;
		}
		return (TRUE);
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == FALSE && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
