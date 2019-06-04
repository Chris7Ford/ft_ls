/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:47:04 by chford            #+#    #+#             */
/*   Updated: 2019/03/04 10:12:04 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		count_words(char const *string, char c)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (string[i] == c)
		i++;
	if (string[i] != '\0')
		count++;
	while (string[i] != '\0')
	{
		if (string[i] == c && string[i + 1] != c && string[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static int		get_word_length(char const *s, char c)
{
	int		length;

	length = 0;
	while (*s != c && *s != '\0')
	{
		length++;
		s++;
	}
	return (length);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**array;
	int			word_length;
	int			size;
	int			i;

	i = 0;
	if (!s)
		return (0);
	size = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (0);
	while (i < size)
	{
		while (*s == c && *s != '\0')
			s++;
		word_length = get_word_length(s, c);
		array[i] = ft_strsub(s, 0, word_length);
		if (!(array[i]))
			return (0);
		s += word_length;
		i++;
	}
	array[i] = 0;
	return (array);
}
