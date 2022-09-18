/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 21:04:45 by junseo            #+#    #+#             */
/*   Updated: 2021/12/04 23:36:14 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*current_node;

	if (!lst)
		return (NULL);
	head = ft_lstnew(f(lst->content));
	if (head == NULL)
	{
		ft_lstclear(&head, del);
		return (NULL);
	}
	current_node = head;
	lst = lst->next;
	while (lst)
	{
		current_node->next = ft_lstnew(f(lst->content));
		if (current_node->next == NULL)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		current_node = current_node->next;
		lst = lst->next;
	}
	return (head);
}
