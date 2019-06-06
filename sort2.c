/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:11:18 by chford            #+#    #+#             */
/*   Updated: 2019/06/06 09:15:56 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_accessed(t_f_node *n1, t_info n2)
{
	if (n1->last_accessed.tv_sec == n2.last_accessed.tv_sec)
	{
		if (!(n1->last_accessed.tv_nsec == n2.last_accessed.tv_nsec))
		{
			return (sort_nanosec(n1->last_accessed.tv_nsec,
						n2.last_accessed.tv_nsec));
		}
		return (sort_alpha_node(n1, n2));
	}
	return (n1->last_accessed.tv_sec < n2.last_accessed.tv_sec);
}

int		sort_modified(t_f_node *n1, t_info n2)
{
	if (n1->last_modified.tv_sec == n2.last_modified.tv_sec)
	{
		if (!(n1->last_modified.tv_nsec == n2.last_modified.tv_nsec))
		{
			return (sort_nanosec(n1->last_modified.tv_nsec,
						n2.last_modified.tv_nsec));
		}
		return (sort_alpha_node(n1, n2));
	}
	return (n1->last_modified.tv_sec < n2.last_modified.tv_sec);
}

int		filter_directory_queue(t_q_link *n1, t_q_link *n2)
{
	char	*s1;
	char	*s2;
	int		i;

	s1 = n1->directory;
	s2 = n2->directory;
	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	if (ft_isalpha(s1[i]) == 0 && s1[i] != '.' && ft_isalpha(s2[i]))
		return (1);
	else if (ft_isalpha(s2[i]) == 0 && s2[i] != '.' && ft_isalpha(s1[i]))
		return (0);
	return (!((s1[i] < s2[i])));
}

int		files_first_alpha(t_in_file *n1, t_in_file *n2)
{
	if (n1->is_directory)
	{
		if (n2->is_directory)
			return (sort_alpha(n1->path, n2->path));
		else
			return (1);
	}
	if (n2->is_directory)
		return (0);
	else
		return (sort_alpha(n1->path, n2->path));
}

int		do_not_sort(t_f_node *n1, t_info n2)
{
	if ((ft_strcmp(n2.f_name, ".") == 0) ||
			(ft_strcmp(n2.f_name, "..") == 0 && ft_strcmp(n1->f_name, ".")))
		return (1);
	return (0);
}
