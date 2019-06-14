/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:12:52 by chford            #+#    #+#             */
/*   Updated: 2019/06/11 12:15:44 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_link_file(char *path)
{
	char	buffer[4097];
	int		count;

	count = readlink(path, buffer, sizeof(buffer));
	if (count != -1)
	{
		buffer[count] = '\0';
		write(1, " -> ", 4);
		write(1, buffer, ft_strlen(buffer));
	}
}

void	print_permission_special(int n, int is_s)
{
	if (is_s)
	{
		if (n & 1)
			write(1, "s", 1);
		else
			write(1, "S", 1);
	}
	else
	{
		if (n & 1)
			write(1, "t", 1);
		else
			write(1, "T", 1);
	}
}

void	print_filename(t_f_node *node, t_input input, char *path)
{
	if (input.show_hidden || !(node->hidden))
	{
		write(1, node->f_name, ft_strlen(node->f_name));
		if (node->is_link && input.flags & _L)
			print_link_file(path);
		ft_putchar('\n');
	}
}
