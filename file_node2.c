/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_node2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:14:50 by chford            #+#    #+#             */
/*   Updated: 2019/06/06 09:07:20 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	handle_right_tree_inbalance(t_f_node **grand)
{
	if ((*grand)->right->left)
		(*grand)->right = right_rotate((*grand)->right);
	*grand = left_rotate(*grand);
}

void	handle_left_tree_inbalance(t_f_node **grand)
{
	if ((*grand)->left->right)
		(*grand)->left = left_rotate((*grand)->left);
	*grand = right_rotate(*grand);
}

void	traverse_nodes_to_insert(t_f_node **orig,
		t_info info, int (*cmp)(t_f_node*, t_info))
{
	int		lenl;
	int		lenr;

	if (cmp(*orig, info))
	{
		if ((*orig)->left)
			traverse_nodes_to_insert(&((*orig)->left), info, cmp);
		else
			(*orig)->left = create_node(info);
	}
	else
	{
		if ((*orig)->right)
			traverse_nodes_to_insert(&((*orig)->right), info, cmp);
		else
			(*orig)->right = create_node(info);
	}
	lenl = get_max_length_node((*orig)->left);
	lenr = get_max_length_node((*orig)->right);
	if (lenl - lenr > 1)
		handle_left_tree_inbalance(orig);
	else if (lenl - lenr < -1)
		handle_right_tree_inbalance(orig);
}

void	insert_node(t_f_node **head, t_info info, int (*cmp)(t_f_node*, t_info))
{
	if (!head)
		return ;
	else if (!(*head))
		*head = create_node(info);
	else
		traverse_nodes_to_insert(head, info, cmp);
}
