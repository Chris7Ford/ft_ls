/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 20:48:28 by chford            #+#    #+#             */
/*   Updated: 2019/02/17 17:26:31 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		length;

	i = 0;
	length = ft_strlen(s1);
	while (s2[i] != '\0' && i < n)
	{
		s1[length] = s2[i];
		i++;
		length++;
	}
	s1[length] = '\0';
	return (s1);
}
