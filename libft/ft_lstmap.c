/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 09:57:32 by chford            #+#    #+#             */
/*   Updated: 2019/02/19 18:36:32 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*temp;
	t_list	*beginning;

	if (!lst || !f)
		return (0);
	temp = f(lst);
	new = ft_lstnew(temp->content, temp->content_size);
	beginning = new;
	lst = lst->next;
	while (lst)
	{
		temp = f(lst);
		new->next = ft_lstnew(temp->content, temp->content_size);
		if (!new->next)
			return (0);
		lst = lst->next;
		new = new->next;
	}
	return (beginning);
}
