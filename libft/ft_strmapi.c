/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:55:06 by junseo            #+#    #+#             */
/*   Updated: 2021/11/20 17:11:11 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	str_len;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	str_len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * str_len + 1);
	if (result == NULL)
		return (NULL);
	while (i < str_len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
