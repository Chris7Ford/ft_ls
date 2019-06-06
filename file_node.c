/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:14:08 by chford            #+#    #+#             */
/*   Updated: 2019/06/05 18:14:24 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_f_node	*create_node(t_info info)
{
	t_f_node	*node;

	node = malloc(sizeof(t_f_node));
	node->f_name = info.f_name;
	node->filetype = info.filetype;
	node->permissions = info.permissions;
	node->last_modified = info.last_modified;
	node->last_accessed = info.last_accessed;
	node->major = info.major;
	node->minor = info.minor;
	node->hidden = info.hidden;
	node->hlink = info.hlink;
	node->error = 0;
	node->size = info.size;
	node->uid = info.uid;
	node->gid = info.gid;
	node->username = info.username;
	node->groupname = info.groupname;
	node->left = 0;
	node->right = 0;
	return (node);
}

void	traverse_nodes_to_get_length(t_f_node *node, int current, int *max)
{
	if (current > *max)
		*max = current;
	if (node->right)
		traverse_nodes_to_get_length(node->right, current + 1, max);
	if (node->left)
		traverse_nodes_to_get_length(node->left, current + 1, max);
	return ;
}

int		get_max_length_node(t_f_node *node)
{
	int		max;

	if (!node)
		return (0);
	max = 1;
	traverse_nodes_to_get_length(node, 1, &max);
	return (max);
}

t_f_node	*left_rotate(t_f_node *grand)
{
	t_f_node	*temp;

	temp = grand->right;
	grand->right = temp->left;
	temp->left = grand;
	return (temp);
}

t_f_node	*right_rotate(t_f_node *grand)
{
	t_f_node	*temp;

	temp = grand->left;
	grand->left = temp->right;
	temp->right = grand;
	return (temp);
}
