/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:56:40 by chford            #+#    #+#             */
/*   Updated: 2019/05/19 10:27:13 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>

typedef struct s_f_node		t_f_node;
struct						s_f_node
{
	char *					f_name;
	struct s_f_node			*right;
	struct s_f_node			*left;
};

typedef struct s_info		t_info;
struct						s_info
{
	char *					f_name;
};
#endif
