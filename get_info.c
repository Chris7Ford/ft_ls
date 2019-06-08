/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:16:58 by chford            #+#    #+#             */
/*   Updated: 2019/06/08 10:22:49 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_file_type(t_info *current, struct stat buf)
{
	if (S_ISBLK(buf.st_mode))
		current->filetype = BLOCK_DEVICE;
	else if (S_ISCHR(buf.st_mode))
		current->filetype = CHARACTER_DEVICE;
	else if (S_ISDIR(buf.st_mode))
		current->filetype = DIRECTORY;
	else if (S_ISFIFO(buf.st_mode))
		current->filetype = FIFO;
	else if (S_ISREG(buf.st_mode))
		current->filetype = REG;
	else if (S_ISLNK(buf.st_mode))
		current->filetype = SYMLINK;
}

int		get_stat_info(t_info *current, char *path,
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

void	get_owner_info(t_info *current)
{
	struct passwd	*pwd;

	pwd = getpwuid(current->uid);
	if (pwd == 0)
		current->username = ft_itoa(current->uid);
	else
		current->username = ft_strdup(pwd->pw_name);
}

void	get_group_info(t_info *current)
{
	struct group	*grp;

	grp = getgrgid(current->gid);
	current->groupname = ft_strdup(grp->gr_name);
}

void	fill_permissions(t_info *current, int st_mode)
{
	current->permissions = st_mode & 7;
	st_mode >>= 3;
	current->permissions = (current->permissions * 10) + (st_mode & 7);
	st_mode >>= 3;
	current->permissions = (current->permissions * 10) + (st_mode & 7);
	st_mode >>= 3;
	current->permissions = (current->permissions * 10) + (st_mode & 7);
}
