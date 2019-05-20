/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 21:13:23 by chford            #+#    #+#             */
/*   Updated: 2019/02/19 18:11:57 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;

	if (ft_strcmp(needle, "") == 0)
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (haystack[i] != '\0')
	{
		while (haystack[i + j] == needle[j])
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
