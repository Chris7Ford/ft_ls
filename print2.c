/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:17:40 by chford            #+#    #+#             */
/*   Updated: 2019/06/09 11:09:12 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_permission_each(int n, int sig, int is_s)
{
	if (n & 4)
		write(1, "r", 1);
	else
		write(1, "-", 1);
	if (n & 2)
		write(1, "w", 1);
	else
		write(1, "-", 1);
	if (sig)
		print_permission_special(n, is_s);
	else if (n & 1)
		write(1, "x", 1);
	else
		write(1, "-", 1);
}

void	print_permissions(t_f_node *node)
{
	int		copy;
	int		sig;

	sig = node->permissions % 10;
	node->permissions /= 10;
	copy = node->permissions;
	print_permission_each(node->permissions % 10, sig & 4, 1);
	node->permissions /= 10;
	print_permission_each(node->permissions % 10, sig & 2, 1);
	node->permissions /= 10;
	print_permission_each(node->permissions % 10, sig & 1, 0);
}

void	print_file_type(t_f_node *current)
{
	if (current->filetype & REG)
		write(1, "-", 1);
	else if (current->filetype & DIRECTORY)
		write(1, "d", 1);
	else if (current->filetype & SYMLINK)
	{
		write(1, "l", 1);
		current->is_link = 1;
	}
	else if (current->filetype & BLOCK_DEVICE)
		write(1, "b", 1);
	else if (current->filetype & CHARACTER_DEVICE)
		write(1, "c", 1);
	else if (current->filetype & FIFO)
		write(1, "p", 1);
	else if (current->filetype & SOCKET)
		write(1, "s", 1);
}

void	print_last_mod(t_f_node *node)
{
	time_t		now;
	time_t		current_time;
	char		*str;

	current_time = node->last_modified.tv_sec;
	str = ctime(&current_time);
	now = time(0);
	write(1, str + 4, 7);
	if ((now - current_time) <= SIX_MONTHS)
		write(1, str + 11, 5);
	else
	{
		write(1, " ", 1);
		write(1, str + 20, 4);
	}
	write(1, " ", 1);
}

void	print_long_file_info(t_f_node *node, t_input input, char *path, int first)
{
	if (input.flags & _A || node->hidden == 0)
	{
		print_file_type(node);
		print_permissions(node);
		write(1, &(node->attrib), 1);
		ft_printf("%3d ", node->hlink);
		if (!(input.flags & _G))
			ft_printf("%-7s", node->username);
		ft_printf(" %s", node->groupname);
		if (node->filetype & BLOCK_DEVICE || node->filetype & CHARACTER_DEVICE)
		{
			ft_printf(" %d,", node->major);
			ft_printf(" %d ", node->minor);
		}
		else
			ft_printf("%7d ", node->size);
		print_last_mod(node);
		print_filename(node, input, path, first);
	}
}
