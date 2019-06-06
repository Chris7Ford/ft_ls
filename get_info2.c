/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:19:17 by chford            #+#    #+#             */
/*   Updated: 2019/06/05 18:21:20 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_long_info(t_info *current, char *directory_name, t_input *input, int first)
{	
	get_stat_info(current, current->f_name, directory_name, input, first);
	get_owner_info(current);
	get_group_info(current);
}

void		get_file_info(t_info *current, t_input *input, char *directory_name, char *filename, int first)
{
	reset_t_info(current);
	current->f_name = ft_strdup(filename);
	get_sort_info(current, directory_name, first);
	if (input->flags & _L)
		get_long_info(current, directory_name, input, first);
}

int		get_sort_info(t_info *current, char *path, int first)
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
