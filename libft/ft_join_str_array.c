/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:52:34 by chford            #+#    #+#             */
/*   Updated: 2019/06/04 17:14:23 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		get_total_char_count(char **tab)
{
	int		count;
	int		i;
	int		j;

	i = 0;
	count = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j++])
			count++;
		i++;
		count++;
	}
	return (count);
}

static void		fill_words(char **tab, char **new, char glue)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	l = 0;
	while (tab[i])
	{
		while (tab[i][j])
			(*new)[l++] = tab[i][j++];
		i++;
		j = 0;
		(*new)[l++] = glue;
	}
	(*new)[l] = '\0';
}

char			*ft_join_str_array(char **tab, char glue)
{
	int		size_total;
	char	*new;

	size_total = get_total_char_count(tab);
	new = (char *)malloc(sizeof(char) * size_total);
	fill_words(tab, &new, glue);
	return (new);
}
