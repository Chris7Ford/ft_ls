/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_ulong_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 10:15:04 by chford            #+#    #+#             */
/*   Updated: 2019/05/09 10:55:06 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	print_hex_ulong_fd(unsigned long n, int fd)
{
	char	array[16];

	ft_strcpy(array, "0123456789abcdef");
	if (n < 16)
	{
		write(fd, &(array[n]), 1);
		return ;
	}
	print_hex_ulong_fd(n / 16, fd);
	write(fd, &(array[n % 16]), 1);
}
