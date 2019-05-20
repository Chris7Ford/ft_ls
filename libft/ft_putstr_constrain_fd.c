/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_constrain_fd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 20:24:27 by chford            #+#    #+#             */
/*   Updated: 2019/05/11 16:30:00 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_constrain_fd(char const *s, int constrain, int fd)
{
	int		len;

	if (!s)
		return ;
	len = ft_strlen(s);
	if (constrain < 0 || len <= constrain)
		write(fd, s, len);
	else
		write(fd, s, constrain);
	return ;
}
