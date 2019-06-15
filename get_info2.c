/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:19:17 by chford            #+#    #+#             */
/*   Updated: 2019/06/15 12:33:37 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_long_info(t_info *current, char *directory_name,
			t_input *input)
{
	if (get_lstat_info(current, directory_name, input) == 0)
		return ;
	get_acl(current, directory_name);
	get_owner_info(current);
	get_group_info(current);
}

void		get_acl(t_info *current, char *directory_name)
{
	acl_entry_t	dummy;
	acl_t		acl;
	int			xattr;

	acl = 0;
	acl = acl_get_link_np(directory_name, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(directory_name, 0, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		current->attrib = '@';
	else if (acl != 0)
		current->attrib = '+';
	else
		current->attrib = ' ';
	acl_free(acl);
}

void		get_file_info(t_info *current, t_input *input, char *directory_name)
{
	char	*path;

	path = file_to_path(directory_name, current->f_name);
	reset_t_info(current);
	get_sort_info(current, path);
	if (input->flags & _L)
		get_long_info(current, path, input);
	free(path);
}

int			get_sort_info(t_info *current, char *path)
{
	struct stat		buf;

	current->hidden = current->f_name[0] == '.' ? 1 : 0;
	if (lstat(path, &buf) != 0)
		return (0);
	fill_file_type(current, buf);
	current->last_modified = buf.st_mtimespec;
	current->last_accessed = buf.st_atimespec;
	return (1);
}

int			get_lstat_info(t_info *current, char *path,
		t_input *input)
{
	struct stat		buf;

	if (lstat(path, &buf) != 0)
		return (0);
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
