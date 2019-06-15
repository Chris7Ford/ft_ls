/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:13:26 by chford            #+#    #+#             */
/*   Updated: 2019/06/14 16:57:52 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*file_to_path(char *path, char *file)
{
	char	*temp;
	char	*temp2;
	int		len;

	if (ft_strcmp(path, "") == 0)
	{
		temp = ft_strdup(file);
		return (temp);
	}
	len = ft_strlen(path);
	if (path[len - 1] != '/')
	{
		temp2 = ft_strdup(path);
		temp2 = ft_strjoin_char(&temp2, '/');
		temp = ft_strjoin(temp2, file);
		free(temp2);
	}
	else
	{
		temp = ft_strjoin(path, file);
	}
	return (temp);
}
