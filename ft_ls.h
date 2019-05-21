/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:56:40 by chford            #+#    #+#             */
/*   Updated: 2019/05/21 10:40:14 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>

# define BLOCK_DEVICE 		1
# define CHARACTER_DEVICE 	2
# define DIRECTORY 			4
# define FIFO				8
# define SYMLINK			16
# define REG				32
# define SOCK				64

typedef struct s_f_node		t_f_node;
struct						s_f_node
{
	struct s_f_node			*right;
	struct s_f_node			*left;
	unsigned int			filetype : 7;
	char *					f_name;
	int						permissions;
	int						hidden : 1;
	int						hlink;
	int						uid;
};

typedef struct s_info		t_info;
struct						s_info
{
	unsigned int			filetype : 7;
	char *					f_name;
	int						permissions;
	int						hidden : 1;
	int						hlink;
	int						uid;
};

int							sort_alpha_node(t_f_node *n1, t_info n2);
int							sort_alpha_node_rev(t_f_node *n1, t_info n2);
void						print_filename_hidden(t_f_node *node);
void						print_filename(t_f_node *node);
t_f_node					*create_node(t_info info);
void						traverse_nodes_to_get_length(t_f_node *node,
							int current, int *max);
int							get_max_length_node(t_f_node *node);
t_f_node					*left_rotate(t_f_node *grand);
t_f_node					*right_rotate(t_f_node *grand);
void						handle_right_tree_inbalance(t_f_node **grand);
void						handle_left_tree_inbalance(t_f_node **grand);
void						traverse_nodes_to_insert(t_f_node **orig,
							t_info info, int (*cmp)(t_f_node*, t_info));
void						insert_node(t_f_node **head,
							t_info info, int (*cmp)(t_f_node*, t_info));
void						inorder_traversal_apply(t_f_node *elem,
							void (*f)(t_f_node*));
void						fill_permissions(t_info *current, int st_mode);
void						print_permission_each(int n);
void						print_permissions(t_f_node *node);
void						get_stat_info(t_info *current, char *f_name);
int							get_directory(char *directory_name,
							t_f_node **head);
void						free_tree(t_f_node *head);
int							main(int argc, char **argv);
#endif
