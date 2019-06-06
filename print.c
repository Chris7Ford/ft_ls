/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:12:52 by chford            #+#    #+#             */
/*   Updated: 2019/06/05 18:13:05 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_link_file(t_f_node *node, char *path)
{
	char	*temp;
	char	buffer[4097];
	int		count;

	temp = file_to_path(path, node->f_name);
	count = readlink(temp, buffer, sizeof(buffer));
	if (count >= 0)
	{
		buffer[count] = '\0';
		write(1, " -> ", 4);
		write(1, buffer, ft_strlen(buffer));
	}
	free(temp);
}

void	print_filename(t_f_node *node, t_input input, char *path)
{
	if (input.show_hidden || !(node->hidden))
	{
		write(1, node->f_name, ft_strlen(node->f_name));
		if (node->is_link && input.flags & _L)
			print_link_file(node, path);
		ft_putchar('\n');
	}
}
