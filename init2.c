/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:28:42 by chford            #+#    #+#             */
/*   Updated: 2019/06/06 09:07:04 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_input_info(t_input *input, int argc, char **argv)
{
	int			i;

	i = 1;
	input->flags = 0;
	while (i < argc && parse_flag(input, argv[i]))
		i++;
	overwrite_ls_flags(input);
	input->directories = 0;
	if (i < argc)
	{
		while (i < argc)
		{
			push_input_file(&(input->directories), argv[i],
					is_directory(argv[i]),
					argc - i > 1 ? 1 : 0);
			i++;
		}
	}
	else
		push_input_file(&(input->directories), ".", 1, 0);
}

void		assign_sorting_function(t_input *input)
{
	if (input->flags & _T)
		input->sort = sort_modified;
	else if (input->flags & _F)
		input->sort = do_not_sort;
	else if (input->flags & _U)
		input->sort = sort_accessed;
	else if (input->flags & _Y)
		input->sort = sort_directories_first_node;
	else if (input->flags & _Z)
		input->sort = sort_length_node;
	else
		input->sort = sort_alpha_node;
}

void		assign_print_function(t_input *input)
{
	if (input->flags & _L)
		input->file_print = print_long_file_info;
	else
		input->file_print = print_filename;
}

void		free_queue(t_q_link *queue)
{
	if (queue->next)
		free_queue(queue->next);
	free(queue->directory);
	free(queue);
}
