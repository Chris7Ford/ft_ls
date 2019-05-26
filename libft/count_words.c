/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 09:16:36 by chford            #+#    #+#             */
/*   Updated: 2019/05/26 09:17:02 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_words(char const *string, char c)
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
