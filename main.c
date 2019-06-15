/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:50:29 by chford            #+#    #+#             */
/*   Updated: 2019/06/15 13:05:11 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_in_sort	get_input_file_sort_function(t_input input)
{
	if (input.flags & _R && input.flags & _T)
		return (sort_input_time_mod_rev);
	else if (input.flags & _R)
		return (files_first_alpha_rev);
	else if (input.flags & _T)
		return (sort_input_time_mod);
	return (files_first_alpha);
}

int			sort_input(t_in_file **head, t_input input)
{
	t_in_file	*elem;
	int			complete;
	int			(*f)(t_in_file *n1, t_in_file *n2);

	complete = 0;
	if (*head == 0 || (*head)->next == 0)
		return (1);
	elem = *head;
	f = get_input_file_sort_function(input);
	if (f(elem, elem->next))
		swap_input_head(head, &complete);
	return (bubble_sort_input(head, f));
}

int			main(int argc, char **argv)
{
	t_in_file	*elem;
	t_input		inp;
	t_info		current;
	int			i;

	init_input(&inp, &current);
	get_input_info(&inp, argc, argv);
	assign_input_functions(&inp);
	i = 0;
	inp.first = sort_input(&(inp.directories), inp);
	elem = inp.directories;
	print_no_exists_err(elem);
	while (elem)
	{
		if (is_dir_m(elem->path, &inp) && !(inp.flags & _D) && !(elem->error))
			get_directory(elem->path, &inp, current);
		else if (!(elem->error))
			print_single_file(elem->path, inp);
		else
			print_no_rights_err_elem(elem);
		elem = elem->next;
	}
	elem = inp.directories;
	free_input(inp.directories);
	return (0);
}
