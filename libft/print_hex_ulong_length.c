/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_ulong_length.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 10:31:23 by chford            #+#    #+#             */
/*   Updated: 2019/05/09 10:31:24 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	print_hex_ulong_length(unsigned long n, int *length)
{
	if (n < 16)
	{
		*length += 1;
		return ;
	}
	print_hex_ulong_length(n / 16, length);
	*length += 1;
}
