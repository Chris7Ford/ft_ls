/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:26:23 by chford            #+#    #+#             */
/*   Updated: 2019/06/05 18:26:36 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_flag(t_input *input, char c)
{
	if (c == 'l')
		input->flags = input->flags | _L;
	else if (c == 'R')
		input->flags = input->flags | _CR;
	else if (c == 'a')
		input->flags = input->flags | _A;
	else if (c == 'r')
		input->flags = input->flags | _R;
	else if (c == 't')
		input->flags = input->flags | _T;
	else if (c == 'u')
		input->flags = input->flags | _U;
	else if (c == 'f')
		input->flags = input->flags | _F;
	else if (c == 'g')
		input->flags = input->flags | _G;
	else if (c == 'd')
		input->flags = input->flags | _D;
	else if (c == 'y')
		input->flags = input->flags | _Y;
	else if (c == 'z')
		input->flags = input->flags | _Z;
	else
		exit_error();
}

int		parse_flag(t_input *input, char *str)
{
	int		i;

	if (str[0] == '-')
	{
		i = 1;
		while (str[i])
			add_flag(input, str[i++]);
		return (1);
	}
	return (0);
}

void	overwrite_ls_flags(t_input *input)
{
	if (input->flags & _G)
		input->flags |= _L;
	if (input->flags & _F && input->flags & _T)
		input->flags -= _T;
	if (input->flags & _F)
	{
		input->flags |= _A;
		if (input->flags & _R)
			input->flags -= _R;
	}
}
