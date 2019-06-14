/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:27:30 by chford            #+#    #+#             */
/*   Updated: 2019/06/13 19:36:00 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_in_file	*create_in_file_node(char *path, int is_dir, int pd)
{
	t_in_file	*elem;

	elem = malloc(sizeof(t_in_file));
	elem->path = ft_strdup(path);
	elem->is_directory = is_dir;
	elem->next = 0;
	elem->error = 0;
	elem->pd = pd;
	return (elem);
}

int			push_input_file(t_in_file **head, char *path, int is_dir, int pd)
{
	t_in_file	*temp;

	temp = *head;
	if (!temp)
	{
		*head = create_in_file_node(path, is_dir, pd);
		check_exists(*head);
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = create_in_file_node(path, is_dir, pd);
		check_exists(temp->next);
	}
	return (1);
}

void		swap_input_head(t_in_file **head, int *complete)
{
	t_in_file	*elem;
	t_in_file	*temp;

	*complete = 0;
	elem = *head;
	*head = elem->next;
	temp = (*head)->next;
	(*head)->next = elem;
	elem->next = temp;
	elem = *head;
}

void		swap_input_links(t_in_file *elem, int *complete)
{
	t_in_file	*other_temp;
	t_in_file	*temp;

	*complete = 0;
	temp = elem->next->next->next;
	other_temp = elem->next;
	elem->next = elem->next->next;
	elem->next->next = other_temp;
	elem->next->next->next = temp;
}

int			bubble_sort_input(t_in_file **head,
		int (*f)(t_in_file *n1, t_in_file *n2))
{
	t_in_file	*elem;
	int			complete;
	int			result;

	complete = 0;
	result = 1;
	elem = *head;
	while (!complete)
	{
		complete = 1;
		if (f(*head, (*head)->next))
			swap_input_head(head, &complete);
		while (elem->next->next)
		{
			if (is_directory(elem->path) || is_directory(elem->next->path))
				result = 0;
			if (f(elem->next, elem->next->next))
				swap_input_links(elem, &complete);
			elem = elem->next;
		}
		elem = *head;
		if (is_directory(elem->next->path))
			result = 0;
	}
	return (result);
}
