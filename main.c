/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:33:47 by chford            #+#    #+#             */
/*   Updated: 2019/05/23 07:20:36 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft/libft.h"

#include <stdio.h>

void print2D(t_f_node *root);

int		sort_alpha_node(t_f_node *n1, t_info n2)
{
	int		i;

	i = 0;
	while ((n1->f_name)[i] == n2.f_name[i] && (n1->f_name)[i] != '\0')
		i++;
	return (!((n1->f_name)[i] < n2.f_name[i]));
}

int		sort_modified(t_f_node *n1, t_info n2)
{
	if (n1->last_modified.tv_sec == n2.last_modified.tv_sec)
		return (sort_alpha_node(n1, n2));
	return (n1->last_modified.tv_sec < n2.last_modified.tv_sec);
}

int		do_not_sort(t_f_node *n1, t_info n2)
{
	return (0);
}

void	print_filename(t_f_node *node)
{
	if (!(node->hidden))
	{
		ft_putstr(node->f_name);
		ft_putchar('\n');
	}
}

t_f_node	*create_node(t_info info)
{
	t_f_node	*node;

	node = malloc(sizeof(t_f_node));
	node->f_name = info.f_name;
	node->filetype = info.filetype;
	node->permissions = info.permissions;
	node->last_modified = info.last_modified;
	node->hidden = info.hidden;
	node->hlink = info.hlink;
	node->size = info.size;
	node->uid = info.uid;
	node->gid = info.gid;
	node->username = info.username;
	node->groupname = info.groupname;
	node->left = 0;
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

void	reverse_inorder_traversal_apply(t_f_node *elem, void (*f)(t_f_node*))
{
	if (elem->right)
		reverse_inorder_traversal_apply(elem->right, f);
	f(elem);
	if (elem->left)
		reverse_inorder_traversal_apply(elem->left, f);
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
	else if (current->filetype & SYMLINK)
	{
		ft_putchar('l');
		current->is_link = 1;
	}
}

void	print_link_file(t_f_node *node) //
{
	char	buffer[4097];
	int		count;

	count = readlink(node->f_name, buffer, sizeof(buffer));
	if (count >= 0)
	{
		buffer[count] = '\0';
//		ft_printf(" -> %s", buffer);
	}
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
//		ft_printf("%s", node->username);
//		ft_printf("%s", node->groupname);
//		ft_printf("%d\n", node->size);
//		if (node->is_link)
//			print_link_file(node);
		ft_putchar('\n');
	}
}

void	fill_file_type(t_info *current, struct stat buf) //
{
	if (S_ISBLK(buf.st_mode))
		current->filetype = BLOCK_DEVICE;
	else if (S_ISCHR(buf.st_mode))
		current->filetype = CHARACTER_DEVICE;
	else if (S_ISDIR(buf.st_mode))
		current->filetype = DIRECTORY;
	else if (S_ISFIFO(buf.st_mode))
		current->filetype = FIFO;
	else if (S_ISREG(buf.st_mode))
		current->filetype = REG;
	else if (S_ISLNK(buf.st_mode))
		current->filetype = SYMLINK;
}

void	get_stat_info(t_info *current, char *f_name)
{
	struct stat		buf;

	lstat(f_name, &buf);
	fill_permissions(current, buf.st_mode);
	fill_file_type(current, buf);
	current->hlink = buf.st_nlink;
	current->size = buf.st_size;
	current->uid = buf.st_uid;
	current->gid = buf.st_gid;
}

void	get_owner_info(t_info *current) //
{
	struct passwd	*pwd;

	pwd = getpwuid(current->uid);
	current->username = ft_strdup(pwd->pw_name);
}

void	get_group_info(t_info *current) //
{
	struct group	*grp;

	grp = getgrgid(current->gid);
	current->groupname = ft_strdup(grp->gr_name);
}

void	get_sort_info(t_info *current) //
{
	struct stat		buf;

	lstat(current->f_name, &buf);
	current->last_modified = buf.st_mtimespec;
	current->hidden = current->f_name[0] == '.' ? 1 : 0;
}

int		get_directory(char *directory_name, t_input *input)
{
	struct dirent	*file;
	t_f_node		*head;
	t_info			current;
	DIR				*directory;

	head = 0;
	directory = opendir(directory_name);
	if (!directory && printf("No such file"))
		return (0);
	while ((file = readdir(directory)))
	{
		current.f_name = ft_strdup(file->d_name);
		get_sort_info(&current);
		get_stat_info(&current, current.f_name);
		get_owner_info(&current);
		get_group_info(&current);
//		insert_node(&head, current, sort_alpha_node);
	//	insert_node(&head, current, do_not_sort);
		insert_node(&head, current, input->sort);
	//	ft_putendl(file->d_name);
	}
	(void)closedir(directory);
//	print2D(head);
	input->for_each_node(head, input->file_print);
	free_tree(head);
	return (1);
}

void	free_tree(t_f_node *head)
{
	if (!(head))
		return ;
	free_tree(head->right);
	free_tree(head->left);
	free(head->f_name);
	free(head->username);
	free(head->groupname);
	free(head);
}

void	add_flag(t_input *input, char c) //
{
	if (c == 'l')
		input->flags = input->flags | L;
	else if (c == 'R')
		input->flags = input->flags | CR;
	else if (c == 'a')
		input->flags = input->flags | A;
	else if (c == 'r')
		input->flags = input->flags | R;
	else if (c == 't')
		input->flags = input->flags | T;
	else if (c == 'u')
		input->flags = input->flags | U;
	else if (c == 'f')
		input->flags = input->flags | F;
	else if (c == 'g')
		input->flags = input->flags | G;
	else if (c == 'd')
		input->flags = input->flags | D;
	else
	{
		ft_putstr("usage: ft_ls [-Radfglrtu] [file ...]\n");
		exit(0);
	}
}

int		parse_flag(t_input *input, char *str) //
{
	int		i;

	if (str[0] == '-')
	{
		i = 1;
		while (str[i])
			add_flag(input, str[i++]);
		return (1);
	}
	return (0);
}

void	overwrite_flags(t_input *input) //
{
	if (input->flags & F && input->flags & T)
		input->flags -= T;
	if (input->flags & F)
		input->flags |= A;
}

void	get_input_info(t_input *input, int argc, char **argv) //
{
	int		i;
	int		j;

	//f flag overwrites t.
	i = 1;
	while (i < argc && parse_flag(input, argv[i]))
		i++;
	overwrite_flags(input);
	j = 1;
	input->directories = (char **)malloc(sizeof(char *) * (argc - i + 2));
	(input->directories)[0] = ft_strdup(".");
	while (i < argc)
		(input->directories)[j++] = strdup(argv[i++]);
	(input->directories)[j] = 0;
}

void	assign_traversal_function(t_input *input) //
{
	if (input->flags & R)
		input->for_each_node = &reverse_inorder_traversal_apply;
	else
		input->for_each_node = &inorder_traversal_apply;
}

void	assign_sorting_function(t_input *input) //
{
	if (input->flags & T)
		input->sort = sort_modified;
	else if (input->flags & F)
		input->sort = do_not_sort;
	else
		input->sort = sort_alpha_node;
}

void	assign_print_function(t_input *input) //
{
	//all possible printing options are..... long and short. Thats it so far...
	if (input->flags & L)
		input->file_print = print_long_file_info;
	else
		input->file_print = print_filename;
}

int		main(int argc, char **argv)
{
	t_input		input;
	int			i;

	get_input_info(&input, argc, argv);
	i = 0;
	assign_sorting_function(&input);
	assign_traversal_function(&input);
	assign_print_function(&input);
	while ((input.directories)[i])
	{
		get_directory(input.directories[i++], &input);
		free(input.directories[i]);
	}
	free(input.directories);
//		get_directory(".", &input);
//		inorder_traversal_apply(head, print_filename); 
//		inorder_traversal_apply(head, print_permissions); 
	return (0);
}
