/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:50:29 by chford            #+#    #+#             */
/*   Updated: 2019/06/05 19:07:30 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_input(t_in_file **head, int (*f)(t_in_file *n1, t_in_file *n2))
{
	t_in_file	*elem;

	if (*head == 0 || (*head)->next == 0)
		return (1);
	elem = *head;
	if (f(elem, elem->next))
		swap_input_head(head);
	return (bubble_sort_input(head, f));
}

int		main(int argc, char **argv)
{
	t_in_file	*elem;
	t_input		input;
	t_info		current;
	int			result;
	int			i;

	init_input(&input);
	reset_t_info(&current);
	get_input_info(&input, argc, argv);
	input.show_hidden = input.flags & _A ? 1 : 0;
	assign_input_functions(&input);
	i = 0;
	result = sort_input(&(input.directories), files_first_alpha);
	elem = input.directories;
	print_no_exists_err(elem);
	while (elem)
	{
		if (is_directory(elem->path) && !(input.flags & _D) && !(elem->error))
			get_directory(elem->path, &input, current, result);
		else if (!(elem->error))
			print_single_file(elem->path, input);
		elem = elem->next;
	}
	elem = input.directories;
	print_no_rights_err_lst(elem);
	free_input(input.directories);
	return (0);
}
