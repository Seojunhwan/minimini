/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:06:03 by junseo            #+#    #+#             */
/*   Updated: 2022/09/19 21:50:04 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_key(char *env)
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

char	*get_env_value(char *env)
{
	// size_t	i;
	size_t	len;
	char	*value;

	len = 0;
	while (env[len] != 0 && env[len] != '=')
		len++;
	if (env[len] == '\0')
		return (NULL);
	value = ft_substr(env, len, ft_strlen(env));
	return (value);
}

t_env_node	*create_env(char *env)
{
	t_env_node	*node;

	node = (t_env_node *)malloc(sizeof(t_env_node));
	if (env == NULL)
	{
		node->key = NULL;
		node->next = NULL;
		node ->value = NULL;
		return (node);
	}
	node->key = get_env_key(env);
	if (node->key == NULL)
		return (NULL);
	node->value = get_env_value(env);
	if (node->value == NULL)
		return (NULL);
	node->next = NULL;
	return (node);
}
