/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 20:18:55 by chford            #+#    #+#             */
/*   Updated: 2019/02/15 21:16:23 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int		i;
	int		length;

	length = 0;
	i = 0;
	length = ft_strlen(s1);
	while (s2[i] != '\0')
	{
		s1[length] = s2[i];
		i++;
		length++;
	}
	s1[length] = '\0';
	return (s1);
}
