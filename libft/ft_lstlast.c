/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:53:33 by junseo            #+#    #+#             */
/*   Updated: 2021/11/17 20:39:36 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*list_ptr;

	list_ptr = lst;
	while (list_ptr != NULL && list_ptr->next != NULL)
		list_ptr = list_ptr->next;
	return (list_ptr);
}
