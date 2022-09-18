/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 23:14:18 by junseo            #+#    #+#             */
/*   Updated: 2021/12/10 17:48:20 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *dest, const char *src, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*src == '\0')
		return ((char *)dest);
	while (i < len && dest[i] != '\0')
	{
		j = 0;
		if (dest[i] == src[j])
		{
			while (dest[i + j] == src[j] && (i + j) < len && src[j] != '\0')
				j++;
			if (src[j] == '\0')
				return ((char *)&dest[i]);
		}
		i++;
	}
	return (NULL);
}
