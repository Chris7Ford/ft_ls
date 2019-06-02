/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 11:27:09 by chford            #+#    #+#             */
/*   Updated: 2019/06/02 11:32:39 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_alpha_node(t_f_node *n1, t_info n2)
{
	int		i;
	int		ret;

	i = 0;
	while ((n1->f_name)[i] == n2.f_name[i] && (n1->f_name)[i] != '\0')
		i++;
	if (ft_isalpha(n1->f_name[i]) == 0 && n1->f_name[i] != '.' && ft_isalpha(n2.f_name[i]))
		ret = 10;
	else if (ft_isalpha(n2.f_name[i]) == 0 && n2.f_name[i] != '.' && ft_isalpha(n1->f_name[i]))
		ret = 11;
//	return (!((n1->f_name)[i] < n2.f_name[i]));
	ret =  (!((n1->f_name)[i] < n2.f_name[i]));
	return (ret);
}

int		main(void)
{
	t_f_node	n1;
	t_info		n2;
	int			ans;

//	_CodeSignature and n2 = Resources
	n1.f_name = "_CodeSignature";
	n2.f_name = "Resources";
	ans = sort_alpha_node(&n1, n2);
	return (0);
}
