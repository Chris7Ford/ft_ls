/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 19:24:45 by chford            #+#    #+#             */
/*   Updated: 2019/03/04 10:05:46 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*link;

	link = (t_list *)malloc(sizeof(t_list));
	if (link)
	{
		if (content)
		{
			if (!(link->content = (void *)malloc(content_size)))
				return (0);
			ft_memcpy(link->content, content, content_size);
			link->content_size = content_size;
			link->next = 0;
		}
		else
		{
			link->content = 0;
			link->content_size = 0;
			link->next = 0;
		}
	}
	else
		return (0);
	return (link);
}
