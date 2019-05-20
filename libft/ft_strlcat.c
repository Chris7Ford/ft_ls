/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 10:04:05 by chford            #+#    #+#             */
/*   Updated: 2019/02/19 19:27:16 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	length;
	size_t	i;

	length = 0;
	while (dst[length] != '\0' && length < dstsize)
		length++;
	i = length;
	while (src[length - i] != '\0' && length + 1 < dstsize)
	{
		dst[length] = src[length - i];
		length++;
	}
	if (i < dstsize)
		dst[length] = '\0';
	return (i + ft_strlen(src));
}
