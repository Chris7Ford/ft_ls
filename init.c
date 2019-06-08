/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:20:47 by chford            #+#    #+#             */
/*   Updated: 2019/06/08 11:33:13 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reset_t_info(t_info *current)
{
	current->major = 0;
	current->attrib = 0;
	current->minor = 0;
	current->filetype = 0;
	current->groupname = 0;
	current->username = 0;
	current->permissions = 0;
	current->hidden = 0;
	current->hlink = 0;
	current->error = 0;
	current->size = 0;
	current->uid = 0;
	current->gid = 0;
}

void	assign_traversal_function(t_input *input)
{
	if (input->flags & _R)
		input->for_each_node = &reverse_inorder_traversal_apply;
	else
		input->for_each_node = &inorder_traversal_apply;
}

void	assign_input_functions(t_input *input)
{
	assign_sorting_function(input);
	assign_traversal_function(input);
	assign_print_function(input);
	input->show_hidden = input->flags & _A ? 1 : 0;
}

void	init_input(t_input *input, t_info *current)
{
	input->dequeue = unshift_queue;
	input->size = 0;
	input->flags = 0;
	input->directories = 0;
	input->show_hidden = 0;
	input->recurse = 0;
	input->size = 0;
	input->show_hidden = input->flags & _A ? 1 : 0;
	reset_t_info(current);
}

void	init_get_directory(t_f_node **head,
		t_q_link **queue, t_input *input)
{
	*head = 0;
	*queue = 0;
	input->size = 0;
}
