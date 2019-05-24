/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepend_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 14:13:35 by chford            #+#    #+#             */
/*   Updated: 2019/05/23 14:15:47 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_prepend_char(char c, char **s1)
{
	int		i;
	char	*string;

	i = 0;
	string = (char *)malloc(sizeof(char) * (ft_strlen(*s1) + 2));
	if (!string)
		return (0);
	string[i++] = c;
	while ((*s1)[i - 1] != '\0')
	{
		string[i] = (*s1)[i - 1];
		i++;
	}
	free(*s1);
	string[i] = '\0';
	return (string);
}
