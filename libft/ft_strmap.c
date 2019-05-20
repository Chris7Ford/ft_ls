/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:34:50 by chford            #+#    #+#             */
/*   Updated: 2019/03/04 10:07:06 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(const char *s, char (*f)(char))
{
	int		i;
	int		size;
	char	*string;

	if (!s)
		return (0);
	size = ft_strlen(s);
	string = (char *)malloc(sizeof(char) * (size + 1));
	if (!string)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		string[i] = f(s[i]);
		i++;
	}
	string[i] = '\0';
	return (string);
}
