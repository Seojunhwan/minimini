/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:18:10 by junseo            #+#    #+#             */
/*   Updated: 2021/11/20 14:21:52 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*s1_ptr;
	const unsigned char		*s2_ptr;

	if (n == 0)
		return (0);
	s1_ptr = (const unsigned char *)s1;
	s2_ptr = (const unsigned char *)s2;
	while (n)
	{
		if (*s1_ptr != *s2_ptr)
			return ((int)(*s1_ptr - *s2_ptr));
		s1_ptr++;
		s2_ptr++;
		n--;
	}
	return (0);
}
