/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:25:16 by chford            #+#    #+#             */
/*   Updated: 2019/06/13 12:19:10 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	exit_error(void)
{
	ft_putstr("usage: ft_ls [-Radfglrtuyz] [file ...]\n");
	exit(0);
}

void	get_directory(char *directory_name,
		t_input *input, t_info current)
{
	struct dirent	*file;
	t_f_node		*head;
	t_q_link		*queue;
	DIR				*directory;

	init_get_directory(&head, &queue, input);
	directory = opendir(directory_name);
	if (check_edge(directory_name, input->first))
		return ;
	if (!directory && print_no_rights_err_str(directory_name, 1))
		return ;
	input->first ? 0 : print_directory_name(directory_name);
	while ((file = readdir(directory)))
	{
		current.f_name = ft_strdup(file->d_name);
		get_file_info(&current, input, directory_name);
		insert_node(&head, current, input->sort);
	}
	(void)closedir(directory);
	input->flags & _L ? ft_printf("total %d\n", input->size) : 0;
	input->for_each_node(head, *input, &queue, directory_name);
	free_tree(head);
	while (input->flags & _CR && queue)
		handle_queue(&queue, directory_name, input);
}
