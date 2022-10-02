/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 01:54:03 by junseo            #+#    #+#             */
/*   Updated: 2022/10/03 04:56:23 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_via_key(char *key)
{
	t_env_node	*curr;

	if (*key == '\0')
		return (NULL);
	curr = g_state.env_head;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

t_env_node	*get_env_node_via_key(char *key)
{
	t_env_node	*curr;

	if (*key == '\0')
		return (NULL);
	curr = g_state.env_head;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

char	*extract_env_key(char *env_str)
{
	size_t	i;
	size_t	len;
	char	*key;

	len = 0;
	while (env_str[len] != 0 && env_str[len] != '=')
	{
		++len;
		if (env_str[len] == '=')
			break ;
	}
	if (env_str[len] == '\0')
		return (NULL);
	key = (char *)ft_malloc(sizeof(char), len + 1);
	i = 0;
	while (i < len)
	{
		key[i] = env_str[i];
		++i;
	}
	key[i] = 0;
	return (key);
}

char	*extract_env_value(char *env_str)
{
	size_t	len;
	char	*value;

	len = 0;
	while (env_str[len] != 0 && env_str[len] != '=')
		len++;
	if (env_str[len] == '\0')
		return (NULL);
	len++;
	value = ft_substr(env_str, len, ft_strlen(env_str));
	return (value);
}

t_env_node	*create_env_node(char *key, char *value)
{
	t_env_node	*node;

	node = (t_env_node *)ft_malloc(sizeof(t_env_node), 1);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}
