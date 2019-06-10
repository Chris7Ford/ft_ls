/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:56:40 by chford            #+#    #+#             */
/*   Updated: 2019/06/09 17:39:51 by chford           ###   ########.fr       */
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
# include <stdio.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include "ft_printf.h"
# include "libft/libft.h"

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
	char						attrib;
	int							permissions;
	int							hlink;
	int							error;
	long						uid;
	long						gid;
};

typedef struct s_info			t_info;
struct							s_info
{
	struct timespec				last_modified;
	struct timespec				last_accessed;
	unsigned int				filetype : 7;
	unsigned int				hidden : 1;
	unsigned int				major;
	unsigned int				minor;
	long long					size;
	char						*groupname;
	char						*username;
	char						*f_name;
	char						attrib;
	int							permissions;
	int							hlink;
	int							error;
	long						uid;
	long						gid;
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
	void						(*for_each_node)(t_f_node *elem, t_input input,
								t_q_link **queue, char *path);
	void						(*file_print)(t_f_node *node,
								t_input input, char *path, int first);
	int							(*sort)(t_f_node *n1, t_info n2);
	int							show_hidden : 1;
	int							recurse : 1;
	int							first;
	int							size;
};

int								sort_alpha(char *str1, char *str2);
int								sort_length_node(t_f_node *n1, t_info n2);
int								sort_alpha_node(t_f_node *n1, t_info n2);
int								sort_directories_first_node(t_f_node *n1,
								t_info n2);
int								is_dir_m(char *path, t_input *input);
int								is_directory(char *path);
void							check_exists(t_in_file *elem);
int								sort_nanosec(long nsec1, long nsec2);
int								sort_accessed(t_f_node *n1, t_info n2);
int								sort_modified(t_f_node *n1, t_info n2);
int								do_not_sort(t_f_node *n1, t_info n2);
void							print_link_file(t_f_node *node, char *path, int first);
void							print_filename(t_f_node *node,
								t_input input, char *path, int first);
char							*file_to_path(char *path, char *file);
t_f_node						*create_node(t_info info);
void							traverse_nodes_to_get_length(t_f_node *node,
								int current, int *max);
int								get_max_length_node(t_f_node *node);
t_f_node						*left_rotate(t_f_node *grand);
t_f_node						*right_rotate(t_f_node *grand);
void							handle_right_tree_inbalance(t_f_node **grand);
void							handle_left_tree_inbalance(t_f_node **grand);
void							traverse_nodes_to_insert(t_f_node **orig,
								t_info info,
								int (*cmp)(t_f_node*, t_info));
void							insert_node(t_f_node **head, t_info info,
								int (*cmp)(t_f_node*, t_info));
void							inorder_traversal_apply(t_f_node *elem,
								t_input input,
								t_q_link **queue, char *path);
void							reverse_inorder_traversal_apply(t_f_node *elem,
								t_input input, t_q_link **queue, char *path);
void							fill_permissions(t_info *current, int st_mode);
void							print_permission_special(int n, int is_s);
void							print_permission_each(int n, int sig, int is_s);
void							print_permissions(t_f_node *node);
void							print_file_type(t_f_node *current);
void							print_last_mod(t_f_node *node);
void							print_long_file_info(t_f_node *node,
								t_input input, char *path, int first);
void							fill_file_type(t_info *current,
									struct stat buf);
int								get_stat_info(t_info *current,
								char *path, t_input *input, int first);
void							get_owner_info(t_info *current);
void							get_group_info(t_info *current);
int								get_sort_info(t_info *current,
								char *path, int first);
t_q_link						*create_link(char *str);
void							push_queue(char *name, t_q_link **head);
t_q_link						*unshift_queue(t_q_link **head);
int								recurse_me(char *directory, t_input input);
void							reset_t_info(t_info *current);
void							get_long_info(t_info *current,
								char *directory_name,
								t_input *input, int first);
void							get_file_info(t_info *current, t_input *input,
								char *directory_name, int first);
void							handle_queue(t_q_link **queue,
								char *directory_name, t_input *input);
void							print_directory_name(char *directory_name);
int								filter_directory_queue(t_q_link *n1,
								t_q_link *n2);
int								swap_queue_head(t_q_link **head);
void							free_in_file(t_in_file *head);
void							init_get_directory(t_f_node **head,
								t_q_link **queue, t_input *input);
int								check_edge(char *path, int first);
void							get_directory(char *directory_name,
								t_input *input, t_info current);
void							free_tree(t_f_node *head);
void							exit_error();
void							add_flag(t_input *input, char c);
int								parse_flag(t_input *input, char *str);
void							overwrite_ls_flags(t_input *input);
t_in_file						*create_in_file_node(char *path,
								int is_dir, int pd);
int								push_input_file(t_in_file **head,
								char *path, int is_dir, int pd);
int								files_first_alpha(t_in_file *n1, t_in_file *n2);
void							swap_input_head(t_in_file **head);
void							swap_input_links(t_in_file *elem,
								int *complete);
int								bubble_sort_input(t_in_file **head,
								int (*f)(t_in_file *n1, t_in_file *n2));
int								sort_input(t_in_file **head,
								int (*f)(t_in_file *n1, t_in_file *n2));
void							get_input_info(t_input *input,
								int argc, char **argv);
void							assign_sorting_function(t_input *input);
void							assign_print_function(t_input *input);
void							free_queue(t_q_link *queue);
void							print_single_file(char *path, t_input input);
void							free_input(t_in_file *file);
int								dont_print_error(char *str);
int								print_no_rights_err_str(char *path, int pd);
void							print_no_rights_err_lst(t_in_file *head);
void							print_no_exists_err(t_in_file *head);
void							assign_input_functions(t_input *input);
void							init_input(t_input *input, t_info *current);
void							get_acl(t_info *current, char *directory_name);
int								get_lstat_info(t_info *current, char *path,
								t_input *input, int first);
int								ends_with_forward_slash(char *str);
#endif
