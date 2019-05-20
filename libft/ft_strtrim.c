/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:06:11 by chford            #+#    #+#             */
/*   Updated: 2019/02/19 16:17:33 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length(char const *s, int i)
{
	int		length;

	length = ft_strlen(s) - 1;
	while (s[length] == ' ' || s[length] == '\n' || s[length] == '\t')
		length--;
	length = length - i + 1;
	if (length < 0)
		length = 0;
	return (length);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		length;
	char	*string;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	length = get_length(s, i);
	string = ft_strnew(length);
	if (!string)
		return (0);
	while (j < (length))
	{
		string[j] = s[i];
		i++;
		j++;
	}
	string[j] = '\0';
	return (string);
}
