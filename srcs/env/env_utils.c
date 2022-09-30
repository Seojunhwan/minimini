/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 01:54:03 by junseo            #+#    #+#             */
/*   Updated: 2022/09/30 02:56:55 by junseo           ###   ########.fr       */
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

char	*extract_env_key(char *env)
{
	size_t	i;
	size_t	len;
	char	*key;

	len = 0;
	while (env[len] != 0 && env[len] != '=')
		++len;
	if (env[len] == '\0')
		return (NULL);
	key = (char *)ft_malloc(sizeof(char), len + 1);
	i = 0;
	while (i < len)
	{
		key[i] = env[i];
		++i;
	}
	key[i] = 0;
	return (key);
}

char	*extract_env_value(char *env)
{
	size_t	len;
	char	*value;

	len = 0;
	while (env[len] != 0 && env[len] != '=')
		len++;
	if (env[len] == '\0')
		return (NULL);
	len++;
	value = ft_substr(env, len, ft_strlen(env));
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
