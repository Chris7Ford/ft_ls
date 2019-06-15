/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:25:16 by chford            #+#    #+#             */
/*   Updated: 2019/06/15 13:39:01 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	exit_error(void)
{
	ft_putstr("usage: ft_ls [-Radfglrtuyz] [file ...]\n");
	exit(0);
}

int		check_printable(t_input input, t_f_node *head, char *path)
{
	struct stat		buf;
	char			*follow;

	if (!head)
		return (0);
	follow = file_to_path(path, head->f_name);
	if ((input.show_hidden || head->hidden == 0) && lstat(follow, &buf))
	{
		free(follow);
		return (0);
	}
	free(follow);
	return (check_printable(input, head->left, path) ||
		check_printable(input, head->right, path));
}

void	print_total(t_input input, t_f_node *head, char *path)
{
	if (input.flags & _L && check_printable(input, head, path))
	{
		write(1, "total ", 6);
		ft_putnbr(input.size);
		write(1, "\n", 1);
	}
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
	print_total(*input, head, directory_name);
	input->for_each_node(head, *input, &queue, directory_name);
	free_tree(head);
	while (input->flags & _CR && queue)
		handle_queue(&queue, directory_name, input);
}
