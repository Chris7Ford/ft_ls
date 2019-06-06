/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:23:40 by chford            #+#    #+#             */
/*   Updated: 2019/06/06 09:12:19 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_tree(t_f_node *head)
{
	if (!(head))
		return ;
	free_tree(head->right);
	free_tree(head->left);
	free(head->f_name);
	free(head->username);
	free(head->groupname);
	free(head);
}

void	free_input(t_in_file *file)
{
	if (file->next)
		free_input(file->next);
	free(file->path);
	free(file);
}

void	free_in_file(t_in_file *head)
{
	if (!head)
		return ;
	if (head->next)
		free_in_file(head->next);
	free(head);
}
