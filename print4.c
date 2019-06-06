/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:30:10 by chford            #+#    #+#             */
/*   Updated: 2019/06/06 09:49:23 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_single_file(char *path, t_input input)
{
	t_f_node	*head;
	t_q_link	*queue;
	t_info		current;

	if (check_edge(path, 1))
		return ;
	if (input.flags & _L)
	{
		head = 0;
		queue = 0;
		current.f_name = ft_strdup(path);
		get_sort_info(&current, path, 1);
		get_stat_info(&current, "00", &input, 1);
		get_owner_info(&current);
		get_group_info(&current);
		insert_node(&head, current, input.sort);
		input.for_each_node(head, input, &queue, path);
		free_tree(head);
	}
	else
		ft_putendl(path);
}

int		dont_print_error(char *str)
{
	if (ft_strcmp(str, "usr") == 0)
		return (1);
	return (0);
}

int		print_no_rights_err_str(char *path, int pd)
{
	char			**path_words;
	int				i;

	i = 0;
	path_words = ft_strsplit(path, '/');
	while (path_words[i])
		i++;
	if ((i > 1 || ft_strcmp(path_words[i - 1], ".")) && errno == 13)
	{
		while (i > 1 && ft_strcmp(path_words[i - 1], ".") == 0)
			i--;
		if (dont_print_error(path_words[i - 1]))
			return (1);
		write(1, "\n", 1);
		pd ? ft_printf("%s:\nft_ls: ", path) : 0;
		ft_printf("%s: ", path_words[i - 1]);
		perror(0);
	}
	free_string_array(&path_words);
	return (1);
}

void	print_no_rights_err_lst(t_in_file *head)
{
	t_in_file		*elem;
	char			**path_words;
	int				i;

	elem = head;
	while (elem && !(i = 0))
	{
		path_words = ft_strsplit(elem->path, '/');
		while (path_words[i])
			i++;
		if ((i > 1 || ft_strcmp(path_words[i - 1], ".")) && errno == 13)
		{
			while (i > 1 && ft_strcmp(path_words[i - 1], ".") == 0)
				i--;
			if (dont_print_error(path_words[i - 1]) && write(1, "\n", 1))
				return ;
			elem->pd ? ft_printf("%s:\n", elem->path) : 0;
			ft_printf("ft_ls: %s: ", path_words[i - 1]);
			perror(0);
		}
		free_string_array(&path_words);
		elem = elem->next;
	}
}

void	print_no_exists_err(t_in_file *head)
{
	t_in_file	*elem;
	struct stat	details;

	elem = head;
	while (elem)
	{
		if (elem->error == 2)
		{
			stat(elem->path, &details);
			write(1, "ft_ls: ", 7);
			write(1, elem->path, ft_strlen(elem->path));
			write(1, ": ", 2);
			perror(0);
		}
		elem = elem->next;
	}
}
