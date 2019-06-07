/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:20:08 by chford            #+#    #+#             */
/*   Updated: 2019/06/06 16:44:07 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_q_link	*create_link(char *str)
{
	t_q_link	*new;

	new = malloc(sizeof(t_q_link));
	new->directory = ft_strdup(str);
	new->next = 0;
	return (new);
}

int			swap_queue_head(t_q_link **head)
{
	t_q_link	*elem;
	t_q_link	*temp;

	elem = *head;
	*head = elem->next;
	temp = (*head)->next;
	(*head)->next = elem;
	elem->next = temp;
	elem = *head;
	return (1);
}

void		push_queue(char *name, t_q_link **head)
{
	t_q_link	*link;

	if (!(*head))
	{
		*head = create_link(name);
		return ;
	}
	link = *head;
	while (link->next)
		link = link->next;
	link->next = create_link(name);
}

void		handle_queue(t_q_link **queue, char *directory_name, t_input *input)
{
	t_q_link		*tmp;
	char			*c_temp;

	tmp = input->dequeue(queue);
	c_temp = tmp->directory;
	tmp->directory = file_to_path(directory_name, tmp->directory);
	free(c_temp);
	if (!(input->flags & L) || ft_strcmp("/tmp", tmp->directory))
		get_directory(tmp->directory, input, tmp->info, 0);
	free(tmp->directory);
	free(tmp);
}

t_q_link	*unshift_queue(t_q_link **head)
{
	t_q_link	*temp;

	temp = *head;
	*head = (*head)->next;
	return (temp);
}
