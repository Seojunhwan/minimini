/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:20:59 by hyuncho           #+#    #+#             */
/*   Updated: 2022/10/03 04:55:57 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_node	*is_in_envp(char *str)
{
	t_env_node	*node;
	char		*key;

	key = extract_env_key(str);
	if (!key)
		key = str;
	node = get_env_node_via_key(key);
	return (node);
}

static int	return_equal_sign_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

void	new_export(char *str)
{
	t_env_node	*new_node;
	t_env_node	*curr;
	int			equal_index;

	if (has_equal_sign(str))
	{
		equal_index = return_equal_sign_index(str);
		new_node = create_env_node(ft_substr(str, 0, equal_index), \
		ft_substr(str, equal_index + 1, ft_strlen(str) - equal_index));
	}
	else
		new_node = create_env_node(ft_strdup(str), NULL);
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
	if (ft_isalpha(str[0]) == false && str[0] != '_')
		return (false);
	if (has_equal_sign(str) == true)
	{
		while (str[i] != '=')
		{
			if (ft_isalnum(str[i]) == false && str[i] != '_')
				return (false);
			i++;
		}
		return (true);
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == false && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
