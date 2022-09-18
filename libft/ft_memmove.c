/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:30:40 by junseo            #+#    #+#             */
/*   Updated: 2021/11/20 13:47:04 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr;

	if (!dst && !src)
		return (NULL);
	dest_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	if (dst <= src)
		while (len--)
			*dest_ptr++ = *src_ptr++;
	else
		while (len--)
			*(dest_ptr + len) = *(src_ptr + len);
	return (dst);
}
