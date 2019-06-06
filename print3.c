/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:22:05 by chford            #+#    #+#             */
/*   Updated: 2019/06/05 18:22:19 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_directory_name(char *directory_name)
{
	write(1, "\n", 1);
	write(1, directory_name, ft_strlen(directory_name));
	write(1, ":\n", 2);
}
