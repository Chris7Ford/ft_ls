/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 09:12:15 by chford            #+#    #+#             */
/*   Updated: 2019/02/19 18:11:34 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;

	if (ft_strcmp(needle, "") == 0)
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)(&(haystack[i])));
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}
