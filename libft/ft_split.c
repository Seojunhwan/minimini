/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:19:22 by junseo            #+#    #+#             */
/*   Updated: 2022/04/10 17:48:46 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	calc_size(char const *s, char c)
{
	size_t	count;
	size_t	i;

	if (!*s)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			count++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		count++;
	return (count);
}

static size_t	get_strlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**release_memory(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char	**splitter(char **split, char const *s, char c, size_t max_count)
{
	size_t	str_len;
	size_t	current_count;

	current_count = 0;
	while (*s != '\0' && current_count < max_count)
	{
		if (*s == c)
			s++;
		else
		{
			str_len = get_strlen(s, c);
			split[current_count] = (char *)malloc(sizeof(char) * str_len + 1);
			if (split[current_count] == NULL)
				return (release_memory(split));
			ft_strlcpy(split[current_count], s, str_len + 1);
			s += str_len;
			current_count++;
		}
	}
	split[current_count] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	max_count;

	if (!s)
		return (NULL);
	while (*s && *s == c)
		s++;
	max_count = calc_size(s, c);
	split = (char **)malloc(sizeof(char *) * (max_count + 1));
	if (split == NULL)
		return (NULL);
	splitter(split, s, c, max_count);
	return (split);
}
