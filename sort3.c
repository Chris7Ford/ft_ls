/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 21:26:20 by chford            #+#    #+#             */
/*   Updated: 2019/06/14 21:28:09 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		files_first_alpha_rev(t_in_file *n1, t_in_file *n2)
{
	if (n1->is_directory)
	{
		if (n2->is_directory)
			return (!(sort_alpha(n1->path, n2->path)));
		else
			return (0);
	}
	if (n2->is_directory)
		return (1);
	else
		return (!(sort_alpha(n1->path, n2->path)));
}

int		sort_input_time_mod(t_in_file *n1, t_in_file *n2)
{
	struct stat	buf;

	lstat(n1->path, &buf);
	n1->last_modified = buf.st_mtimespec;
	lstat(n2->path, &buf);
	n2->last_modified = buf.st_mtimespec;
	if (n1->last_modified.tv_sec == n2->last_modified.tv_sec)
	{
		if (!(n1->last_modified.tv_nsec == n2->last_modified.tv_nsec))
		{
			return (sort_nanosec(n1->last_modified.tv_nsec,
						n2->last_modified.tv_nsec));
		}
		return (sort_alpha(n1->path, n2->path));
	}
	return (n1->last_modified.tv_sec < n2->last_modified.tv_sec);
}

int		sort_input_time_mod_rev(t_in_file *n1, t_in_file *n2)
{
	struct stat	buf;

	lstat(n1->path, &buf);
	n1->last_modified = buf.st_mtimespec;
	lstat(n2->path, &buf);
	n2->last_modified = buf.st_mtimespec;
	if (n1->last_modified.tv_sec == n2->last_modified.tv_sec)
	{
		if (!(n1->last_modified.tv_nsec == n2->last_modified.tv_nsec))
		{
			return ((!sort_nanosec(n1->last_modified.tv_nsec,
						n2->last_modified.tv_nsec)));
		}
		return (!(sort_alpha(n1->path, n2->path)));
	}
	return (!(n1->last_modified.tv_sec < n2->last_modified.tv_sec));
}
