/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:53:43 by chford            #+#    #+#             */
/*   Updated: 2019/05/23 14:15:17 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_free(char **s1, char **s2, int free1, int free2)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	j = 0;
	string = (char *)malloc(sizeof(char) *
			(ft_strlen(*s1) + ft_strlen(*s2) + 1));
	if (!string)
		return (0);
	while ((*s1)[i] != '\0')
	{
		string[i] = (*s1)[i];
		i++;
	}
	while ((*s2)[j] != '\0')
		string[i++] = (*s2)[j++];
	string[i] = '\0';
	if (free1)
		free(*s1);
	if (free2)
		free(*s2);
	return (string);
}
