/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:33:47 by chford            #+#    #+#             */
/*   Updated: 2019/05/21 10:43:19 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>

int		sort_alpha_node(t_f_node *n1, t_info n2)
{
	int		i;

	i = 0;
	while ((n1->f_name)[i] == n2.f_name[i] && (n1->f_name)[i] != '\0')
		i++;
	return (!((n1->f_name)[i] < n2.f_name[i]));
}

int		sort_alpha_node_rev(t_f_node *n1, t_info n2)
{
	int		i;

	i = 0;
	while ((n1->f_name)[i] == n2.f_name[i] && (n1->f_name)[i] != '\0')
		i++;
	return ((n1->f_name)[i] < n2.f_name[i]);
}

void	print_filename(t_f_node *node)
{
	ft_putstr(node->f_name);
	ft_putchar('\n');
}

t_f_node	*create_node(t_info info)
{
	t_f_node	*node;

	node = malloc(sizeof(t_f_node));
	node->f_name = info.f_name;
	node->filetype = info.filetype;
	node->permissions = info.permissions;
	node->hidden = info.hidden;
	node->hlink = info.hlink;
	node->left = 0;
	node->uid = info->uid;
	node->right = 0;
	return (node);
}

void	traverse_nodes_to_get_length(t_f_node *node, int current, int *max)
{
	if (current > *max)
		*max = current;
	if (node->right)
		traverse_nodes_to_get_length(node->right, current + 1, max);
	if (node->left)
		traverse_nodes_to_get_length(node->left, current + 1, max);
	return ;
}

/*void	traverse_nodes_to_get_length(t_f_node *node, int current, int *max)
{
	ft_putstr("Current = ");
	ft_putnbr(current);
	ft_putstr(" and filename = ");
	ft_putendl(node->f_name);
	if (current > *max)
		*max = current;
	if (node->right)
	{
		ft_putstr("Heading to the right\n");
		traverse_nodes_to_get_length(node->right, current + 1, max);
		ft_putstr("Going back up to where current = ");
		ft_putnbr(current);
		ft_putchar('\n');
	}
	if (node->left)
	{
		ft_putstr("Heading to the left\n");
		traverse_nodes_to_get_length(node->left, current + 1, max);
	}
	return ;
}*/

int		get_max_length_node(t_f_node *node)
{
	int		max;

	if (!node)
		return (0);
	max = 1;
	traverse_nodes_to_get_length(node, 1, &max);
	return (max);
}

t_f_node	*left_rotate(t_f_node *grand)
{
	t_f_node	*temp;

	temp = grand->right;
	grand->right = temp->left;
	temp->left = grand;
	return (temp);
}

t_f_node	*right_rotate(t_f_node *grand)
{
	t_f_node	*temp;

	temp = grand->left;
	grand->left = temp->right;
	temp->right = grand;
	return (temp);
}

void	handle_right_tree_inbalance(t_f_node **grand)
{
	if ((*grand)->right->left)
		(*grand)->right = right_rotate((*grand)->right);
	*grand = left_rotate(*grand);
}

void	handle_left_tree_inbalance(t_f_node **grand)
{
	if ((*grand)->left->right)
		(*grand)->left = left_rotate((*grand)->left);
	*grand = right_rotate(*grand);
//	printf("after handling the left tree inbalance, the structof the tree looks like this:\n");
//	printf("          %s\n",(*grand)->f_name);
//	printf("%s                  %s\n",(*grand)->left->f_name, (*grand)->right->f_name);
}

void	traverse_nodes_to_insert(t_f_node **orig, t_info info, int (*cmp)(t_f_node*, t_info))
{
	int		lenl;
	int		lenr;

	if (cmp(*orig, info))
	{
		if ((*orig)->left)
			traverse_nodes_to_insert(&((*orig)->left), info, cmp);
		else
			(*orig)->left = create_node(info);
	}
	else
	{
		if ((*orig)->right)
			traverse_nodes_to_insert(&((*orig)->right), info, cmp);
		else
			(*orig)->right = create_node(info);
	}
	lenl = get_max_length_node((*orig)->left);
	lenr = get_max_length_node((*orig)->right);
	if (lenl - lenr > 1)
		handle_left_tree_inbalance(orig);
	else if (lenl - lenr < -1)
		handle_right_tree_inbalance(orig);
}

void	insert_node(t_f_node **head, t_info info, int (*cmp)(t_f_node*, t_info))
{
	if (!head)
		return ;
	else if (!(*head))
		*head = create_node(info);
	else
		traverse_nodes_to_insert(head, info, cmp);
}

void	inorder_traversal_apply(t_f_node *elem, void (*f)(t_f_node*))
{
	if (elem->left)
		inorder_traversal_apply(elem->left, f);
	f(elem);
	if (elem->right)
		inorder_traversal_apply(elem->right, f);
}

void	fill_permissions(t_info *current, int st_mode)
{
	current->permissions = st_mode & 7;
	st_mode >>= 3;
	current->permissions = (current->permissions * 10) + (st_mode & 7);
	st_mode >>= 3;
	current->permissions = (current->permissions * 10) + (st_mode & 7);
}

void	print_permission_each(int n)
{
	if (n & 4)
		ft_putchar('r');
	else
		ft_putchar('-');
	if (n & 2)
		ft_putchar('w');
	else
		ft_putchar('-');
	if (n & 1)
		ft_putchar('x');
	else
		ft_putchar('-');
}

void	print_permissions(t_f_node *node)
{
	int		copy;

	copy = node->permissions;
	print_permission_each(node->permissions % 10);
	node->permissions /= 10;
	print_permission_each(node->permissions % 10);
	node->permissions /= 10;
	print_permission_each(node->permissions % 10);
}

void	print_file_type(t_f_node *current)
{
	if (current->filetype & REG)
		ft_putchar('-');
	else if (current->filetype & DIRECTORY)
		ft_putchar('d');
}

void	print_long_file_info(t_f_node *node) //
{
	if (node->hidden == 0)
	{
		print_file_type(node);
		print_permissions(node);
		ft_putchar(' ');
		print_filename(node);
//		ft_printf("%4d", node->hlink);
	}
}

void	fill_file_type(t_info *current, struct stat buf) //
{
	//This will have to be double checked because it says regular files and directories are something else if the order is different..
	if (buf.st_mode & S_IFREG)
//		printf("regular file\n");
		current->filetype = REG;
	else if (buf.st_mode & S_IFDIR)
	//	printf("directory\n");
		current->filetype = DIRECTORY;
	else if (buf.st_mode & S_IFBLK)
//		printf("block device\n");
		current->filetype = BLOCK_DEVICE;
	else if (buf.st_mode & S_IFCHR)
//		printf("character device");
		current->filetype = CHARACTER_DEVICE;
	else if (buf.st_mode & S_IFIFO)
//		printf("FIFO/pipe\n");
		current->filetype = FIFO;
	else if (buf.st_mode & S_IFLNK)
//		printf("symlink\n");
		current->filetype = SYMLINK;
	else if (buf.st_mode & S_IFSOCK)
//		printf("socket\n");
		current->filetype = SOCK;
}

void	get_stat_info(t_info *current, char *f_name)
{
	struct stat		buf;

	stat(f_name, &buf);
	fill_permissions(current, buf.st_mode);
	fill_file_type(current, buf);
	//These are being stored backwards, so I'll print backwards later..
	current->hlink = buf.st_nlink;
	current->uid = buf.st_uid;
}

int		get_directory(char *directory_name, t_f_node **head)
{
	struct dirent	*file;
	t_info			current;
	DIR				*directory;

	directory = opendir(directory_name);
	if (!directory && printf("No such file"))
		return (0);
	while ((file = readdir(directory)))
	{
		current.f_name = ft_strdup(file->d_name);
		current.hidden = file->d_name[0] == '.' ? 1 : 0;
		get_stat_info(&current, current.f_name);
		insert_node(head, current, sort_alpha_node);
	//	ft_putendl(file->d_name);
	}
	(void)closedir(directory);
	return (1);
}

void	free_tree(t_f_node *head)
{
	if (!(head))
		return ;
	free_tree(head->right);
	free_tree(head->left);
	free(head->f_name);
	free(head);
}

int		main(int argc, char **argv)
{
	t_f_node	*head;
	head = 0;
	if (argc == 1)
	{
		get_directory(".", &head);
//		inorder_traversal_apply(head, print_filename); 
//		inorder_traversal_apply(head, print_permissions); 
		inorder_traversal_apply(head, print_long_file_info); 
		free_tree(head);
	}
	return (0);
}
