/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:16:21 by chford            #+#    #+#             */
/*   Updated: 2019/06/06 08:52:52 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	inorder_traversal_apply(t_f_node *elem,
		t_input input, t_q_link **queue, char *path)
{
	if (elem->left)
		inorder_traversal_apply(elem->left, input, queue, path);
	input.file_print(elem, input, path);
	if (input.flags & _CR && elem->filetype & DIRECTORY
			&& recurse_me(elem->f_name, input))
		push_queue(elem->f_name, queue);
	if (elem->right)
		inorder_traversal_apply(elem->right, input, queue, path);
}

void	reverse_inorder_traversal_apply(t_f_node *elem,
		t_input input, t_q_link **queue, char *path)
{
	if (elem->right)
		reverse_inorder_traversal_apply(elem->right, input, queue, path);
	input.file_print(elem, input, path);
	if (input.flags & _CR && elem->filetype & DIRECTORY
			&& recurse_me(elem->f_name, input))
		push_queue(elem->f_name, queue);
	if (elem->left)
		reverse_inorder_traversal_apply(elem->left, input, queue, path);
}
