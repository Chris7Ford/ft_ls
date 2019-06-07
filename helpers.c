/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:10:06 by chford            #+#    #+#             */
/*   Updated: 2019/06/06 17:08:59 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_directory(char *path)
{
	struct stat	details;

	stat(path, &details);
	return (S_ISDIR(details.st_mode));
}

int		is_directory_main(char *path, t_input *input)
{
	struct stat	details;

	stat(path, &details);
	return (S_ISDIR(details.st_mode) &&
			((ft_strcmp(path, "/tmp")) || !(input->flags & _L)));
}

int		recurse_me(char *directory, t_input input)
{
	if (input.show_hidden || directory[0] != '.')
	{
		if (ft_strcmp(directory, ".") == 0 || ft_strcmp(directory, "..") == 0)
			return (0);
		return (1);
	}
	return (0);
}

int		check_edge(char *path, int first)
{
	if (ft_strncmp(path, "/d", 2) == 0)
	{
		if (ft_strcmp(path, "/dev/fd/3") == 0 ||
				ft_strcmp(path, "/dev/fd/3/") == 0)
		{
			if (!first)
				write(1, "\n/dev/fd/3:\nft_ls: 3: Not a directory\n", 39);
			else
				write(1, "ft_ls: /dev/fd/3: Bad file descriptor\n", 38);
			return (1);
		}
		else if (ft_strcmp(path, "/dev/fd/4") == 0 ||
				ft_strcmp(path, "/dev/fd/4/") == 0)
		{
			if (!first)
				write(1, "ft_ls: 4: directory causes a cycle\n", 36);
			else
				write(1, "ft_ls: /dev/fd/4: Bad file descriptor\n", 38);
			return (1);
		}
	}
	return (0);
}

void	check_exists(t_in_file *elem)
{
	struct stat	details;
	DIR			*directory;

	directory = opendir(elem->path);
	if (stat(elem->path, &details) == -1 || !directory)
	{
		if (errno == 2 || errno == 13)
			elem->error = errno;
	}
	if (directory)
		(void)closedir(directory);
}
