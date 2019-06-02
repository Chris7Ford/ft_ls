/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:56:40 by chford            #+#    #+#             */
/*   Updated: 2019/06/02 11:29:56 by chford           ###   ########.fr       */
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
# include <errno.h>
# include "ft_printf.h"

# define BLOCK_DEVICE 			1
# define CHARACTER_DEVICE	 	2
# define DIRECTORY 				4
# define FIFO					8
# define SYMLINK				16
# define REG					32
# define SOCKET					64
# define _L						1
# define _CR					2
# define _A						4
# define _R						8
# define _T						16
# define _U						32
# define _F						64
# define _G						128
# define _D						256
# define _Y						512
# define _Z						1024
# define ALPHA					1
# define LAST_MOD				2
# define DO_NOT_SORT			4
# define LAST_ACCESS			8
# define SIX_MONTHS				15780000

typedef struct s_f_node			t_f_node;
struct							s_f_node
{
	struct timespec				last_modified;
	struct timespec				last_accessed;
	struct s_f_node				*right;
	struct s_f_node				*left;
	unsigned int				filetype : 7;
	unsigned int				is_link : 1;
	unsigned int				hidden : 1;
	unsigned int				major;
	unsigned int				minor;
	long long					size;
	char						*username;
	char						*groupname;
	char						*f_name;
	int							permissions;
	int							hlink;
	int							error;
	int							uid;
	int							gid;
};

typedef struct s_info			t_info;
struct							s_info
{
	struct timespec				last_modified;
	struct timespec				last_accessed;
	unsigned int				device_detected;
	unsigned int				filetype : 7;
	unsigned int				hidden : 1;
	unsigned int				major;
	unsigned int				minor;
	long long					size;
	char						*groupname;
	char						*username;
	char						*f_name;
	int							permissions;
	int							hlink;
	int							error;
	int							uid;
	int							gid;
};

typedef struct s_q_link			t_q_link;
struct							s_q_link
{
	t_q_link					*next;
	t_info						info;
	char						*directory;
};

typedef struct s_in_file		t_in_file;
struct							s_in_file
{
	t_in_file					*next;
	char						*path;
	unsigned int				is_directory : 1;
	int							error;
	int							pd;
};

typedef struct s_input			t_input;
struct							s_input
{
	unsigned int				flags : 11;
	t_in_file					*directories;
	t_q_link					*(*dequeue)(t_q_link **head);
	void						(*for_each_node)(t_f_node *elem, t_input input, void (*f)
								(t_f_node *node, t_input input));
	void						(*file_print)(t_f_node *node, t_input input);
	int							(*sort)(t_f_node *n1, t_info n2);
	int							show_hidden : 1;
	int							recurse : 1;
	int							size;
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
int								get_stat_info(t_info *current, char *f_name, char *path,
								t_input *input);
void							get_directory(char *directory_name,
								t_input *input, t_info current, int first);
void							free_tree(t_f_node *head);
#endif
