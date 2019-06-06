/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:53:43 by chford            #+#    #+#             */
/*   Updated: 2019/06/06 09:20:49 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_char(char **s1, char c)
{
	char	*string;
	int		i;

	i = 0;
	string = (char *)malloc(sizeof(char) * (ft_strlen(*s1) + 2));
	if (!string)
		return (0);
	while ((*s1)[i] != '\0')
	{
		string[i] = (*s1)[i];
		i++;
	}
	free(*s1);
	string[i] = c;
	string[i + 1] = '\0';
	return (string);
}
