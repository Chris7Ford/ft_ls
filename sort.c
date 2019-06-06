/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:56:13 by chford            #+#    #+#             */
/*   Updated: 2019/06/05 17:56:36 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_alpha(char *str1, char *str2)
{
	int		i;
	
	i = 0;
	while (str1[i] == str2[i] && str1[i] != '\0')
		i++;
	return (str1[i] > str2[i]);
}

int		sort_length_node(t_f_node *n1, t_info n2)
{
	int		len1;
	int		len2;

	len1 = ft_strlen(n1->f_name);
	len2 = ft_strlen(n2.f_name);

	if (len1 > len2)
		return (0);
	if (len1 < len2)
		return (1);
	return (sort_alpha(n1->f_name, n2.f_name));
}

int		sort_alpha_node(t_f_node *n1, t_info n2)
{
	int		i;
	int		ret;

	i = 0;
	while ((n1->f_name)[i] == n2.f_name[i] && (n1->f_name)[i] != '\0')
		i++;
	if (ft_isalnum(n1->f_name[i]) == 0 && n1->f_name[i] != '.' && ft_isupper(n2.f_name[i]))
		ret = 1;
	else if (ft_isalnum(n1->f_name[i]) == 0 && n1->f_name[i] != '.' && ft_islower(n2.f_name[i]))
		ret = 0;
	else if (ft_isalnum(n2.f_name[i]) == 0 && n2.f_name[i] != '.' && ft_isupper(n1->f_name[i]))
		ret = 0;
	else if (ft_isalnum(n2.f_name[i]) == 0 && n2.f_name[i] != '.' && ft_islower(n1->f_name[i]))
		ret = 1;
	else
		ret =  (!((n1->f_name)[i] < n2.f_name[i]));
	return (ret);
}

int		sort_directories_first_node(t_f_node *n1, t_info n2)
{
	if (is_directory(n1->f_name))
	{
		if (is_directory(n2.f_name))
			return (sort_alpha(n1->f_name, n2.f_name));
		return (0);
	}
	if (is_directory(n2.f_name))
		return (1);
	return (sort_alpha(n1->f_name, n2.f_name));
}
