/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:19:17 by chford            #+#    #+#             */
/*   Updated: 2019/06/08 18:40:54 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_long_info(t_info *current, char *directory_name,
			t_input *input, int first)
{
	if (ends_with_forward_slash(directory_name))
		get_stat_info(current, directory_name, input, first);
	else
		get_lstat_info(current, directory_name, input, first);
	get_acl(current, directory_name);
	get_owner_info(current);
	get_group_info(current);
}

void		get_acl(t_info *current, char *directory_name)
{
	char	*path;
	int		xattr;

	path = file_to_path(directory_name, current->f_name);
	xattr = listxattr(path, 0, 0, XATTR_NOFOLLOW);
	if (xattr > 0)
		current->attrib |= EXT_AT;
	free(path);
}

void		get_file_info(t_info *current, t_input *input, char *directory_name,
			int first)
{
	reset_t_info(current);
	get_sort_info(current, directory_name, first);
	if (input->flags & _L)
		get_long_info(current, directory_name, input, first);
}

int			get_sort_info(t_info *current, char *path, int first)
{
	struct stat		buf;
	char			*temp;

	if (lstat(current->f_name, &buf) == -1 || !first)
	{
		temp = file_to_path(path, current->f_name);
		lstat(temp, &buf);
		free(temp);
	}
	fill_file_type(current, buf);
	current->last_modified = buf.st_mtimespec;
	current->last_accessed = buf.st_atimespec;
	current->hidden = current->f_name[0] == '.' ? 1 : 0;
	return (1);
}

int		get_lstat_info(t_info *current, char *path,
		t_input *input, int first)
{
	struct stat		buf;
	char			*temp;

	if (lstat(current->f_name, &buf) == -1 || !first)
	{
		temp = file_to_path(path, current->f_name);
		if (lstat(temp, &buf) == -1)
			return (0);
	}
	if (current->filetype & BLOCK_DEVICE ||
			current->filetype & CHARACTER_DEVICE)
	{
		current->major = major(buf.st_rdev);
		current->minor = minor(buf.st_rdev);
	}
	fill_permissions(current, buf.st_mode);
	current->hlink = buf.st_nlink;
	current->size = buf.st_size;
	if (current->hidden == 0 || input->show_hidden)
		input->size += buf.st_blocks;
	current->uid = buf.st_uid;
	current->gid = buf.st_gid;
	return (1);
}
