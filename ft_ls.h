/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:56:40 by chford            #+#    #+#             */
/*   Updated: 2019/05/23 18:52:38 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <unistd.h>

# define BLOCK_DEVICE 			1
# define CHARACTER_DEVICE	 	2
# define DIRECTORY 				4
# define FIFO					8
# define SYMLINK				16
# define REG					32
//# define SOCK					64
# define L						1
# define CR						2
# define A						4
# define R						8
# define T						16
# define U						32
# define F						64
# define G						128
# define D						256
# define ALPHA					1
# define LAST_MOD				2
# define DO_NOT_SORT			4

typedef struct s_f_node			t_f_node;
struct							s_f_node
{
	struct timespec				last_modified;
	struct s_f_node				*right;
	struct s_f_node				*left;
	unsigned int				filetype : 7;
	char						*username;
	char						*groupname;
	char						*f_name;
	int							permissions;
	int							is_link : 1;
	int							hidden : 1;
	int							hlink;
	int							size;
	int							uid;
	int							gid;
};

typedef struct s_info			t_info;
struct							s_info
{
	struct timespec				last_modified;
	unsigned int				filetype : 7;
	char						*groupname;
	char						*username;
	char						*f_name;
	int							permissions;
	int							hidden : 1;
	int							hlink;
	int							size;
	int							uid;
	int							gid;
};

typedef struct s_input			t_input;
struct							s_input
{
	void						(*for_each_node)(t_f_node *elem, t_input input, void (*f)
								(t_f_node *node, t_input input));
	void						(*file_print)(t_f_node *node, t_input input);
	char						**directories;
	int							(*sort)(t_f_node *n1, t_info n2);
	int							show_hidden : 1;
	int							recurse : 1;
	int							flags : 9;
};

typedef struct s_q_link			t_q_link;
struct							s_q_link
{
	t_q_link					*next;
	t_info						info;
	char						*directory;
};

int								sort_alpha_node(t_f_node *n1, t_info n2);
void							print_filename(t_f_node *node, t_input input);
t_f_node						*create_node(t_info info);
void							traverse_nodes_to_get_length(t_f_node *node,
								int current, int *max);
int								get_max_length_node(t_f_node *node);
t_f_node						*left_rotate(t_f_node *grand);
t_f_node						*right_rotate(t_f_node *grand);
void							handle_right_tree_inbalance(t_f_node **grand);
void							handle_left_tree_inbalance(t_f_node **grand);
void							traverse_nodes_to_insert(t_f_node **orig,
								t_info info, int (*cmp)(t_f_node*, t_info));
void							insert_node(t_f_node **head,
								t_info info, int (*cmp)(t_f_node*, t_info));
void							inorder_traversal_apply(t_f_node *elem, t_input input,
								void (*f)(t_f_node*, t_input));
void							fill_permissions(t_info *current, int st_mode);
void							print_permission_each(int n);
void							print_permissions(t_f_node *node);
int								get_stat_info(t_info *current, char *f_name);
int								get_directory(char *directory_name,
								t_input *input, t_info current);
void							free_tree(t_f_node *head);
int								main(int argc, char **argv);
#endif
