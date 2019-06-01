/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:50:29 by chford            #+#    #+#             */
/*   Updated: 2019/05/31 18:19:25 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft/libft.h"

#include <stdio.h>

int		is_directory(char *path)
{
	struct stat	details;

	stat(path, &details);
	return (S_ISDIR(details.st_mode));
}

int		sort_alpha(char *str1, char *str2)
{
	int		i;
	
	i = 0;
	while (str1[i] == str2[i] && str1[i] != '\0')
		i++;
	return (str1[i] > str2[i]);
}

int		sort_length_node(t_f_node *n1, t_info n2)
{
	int		len1;
	int		len2;

	len1 = ft_strlen(n1->f_name);
	len2 = ft_strlen(n2.f_name);

	if (len1 > len2)
		return (0);
	if (len1 < len2)
		return (1);
	return (sort_alpha(n1->f_name, n2.f_name));
}

int		sort_alpha_node(t_f_node *n1, t_info n2)
{
	int		i;

	i = 0;
	while ((n1->f_name)[i] == n2.f_name[i] && (n1->f_name)[i] != '\0')
		i++;
	return (!((n1->f_name)[i] < n2.f_name[i]));
}

int		sort_directories_first_node(t_f_node *n1, t_info n2)
{
	if (is_directory(n1->f_name))
	{
		if (is_directory(n2.f_name))
			return (sort_alpha(n1->f_name, n2.f_name));
		return (0);
	}
	if (is_directory(n2.f_name))
		return (1);
	return (sort_alpha(n1->f_name, n2.f_name));
}

void	check_exists(t_in_file *elem)
{
	struct stat	details;
	struct dirent	*file;
	DIR				*directory;

	directory = opendir(elem->path);
	if (stat(elem->path, &details) == -1 || !directory)
	{
		if (errno == 2 || errno == 13)
			elem->error = errno;
	}
}

int		sort_accessed(t_f_node *n1, t_info n2)
{
	if (n1->last_accessed.tv_sec == n2.last_accessed.tv_sec)
		return (sort_alpha_node(n1, n2));
	return (n1->last_accessed.tv_sec < n2.last_accessed.tv_sec);
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

void	print_link_file(t_f_node *node) //
{
	char	buffer[4097];
	int		count;

	count = readlink(node->f_name, buffer, sizeof(buffer));
	if (count >= 0)
	{
		buffer[count] = '\0';
		write(1, " -> ", 4);
		write(1, buffer, ft_strlen(buffer));
	}
}

void	print_filename(t_f_node *node, t_input input)
{
	if (input.show_hidden || !(node->hidden))
	{
		write(1, node->f_name, ft_strlen(node->f_name));
		if (node->is_link && input.flags & L)
			print_link_file(node);
		ft_putchar('\n');
	}
}

char		*file_to_path(char *path, char *file)
{
	char	*temp;
	char	*temp2;
	int		len;

	len = ft_strlen(path);
	if (path[len - 1] != '/')
	{
		temp2 = ft_strdup(path);
		temp2 = ft_strjoin_char(&temp2, '/');
		temp = ft_strjoin(temp2, file);
		free(temp2);
	}
	else
	{
		temp = ft_strjoin(path, file);
	}
//	free(file);
	return (temp);
}

t_f_node	*create_node(t_info info)
{
	t_f_node	*node;

	node = malloc(sizeof(t_f_node));
	node->f_name = info.f_name;
	node->filetype = info.filetype;
	node->permissions = info.permissions;
	node->last_modified = info.last_modified;
	node->last_accessed = info.last_accessed;
	node->major = info.major;
	node->minor = info.minor;
	node->hidden = info.hidden;
	node->hlink = info.hlink;
	node->error = 0;
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

void	inorder_traversal_apply(t_f_node *elem, t_input input, void (*f)(t_f_node*, t_input))
{
	if (elem->left)
		inorder_traversal_apply(elem->left, input, f);
	f(elem, input);
	if (elem->right)
		inorder_traversal_apply(elem->right, input, f);
}

void	reverse_inorder_traversal_apply(t_f_node *elem, t_input input, void (*f)(t_f_node*, t_input))
{
	if (elem->right)
		reverse_inorder_traversal_apply(elem->right, input, f);
	f(elem, input);
	if (elem->left)
		reverse_inorder_traversal_apply(elem->left, input, f);
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
	else if (current->filetype & BLOCK_DEVICE)
		write(1, "b", 1);
	else if (current->filetype & CHARACTER_DEVICE)
		write(1, "c", 1);
	else if (current->filetype & FIFO)
		write(1, "p", 1);
	else if (current->filetype & SOCKET)
		write(1, "s", 1);
}

void	print_last_mod(t_f_node *node)
{
	time_t		now;
	time_t		current_time;
	char		*str;

	current_time = node->last_modified.tv_sec;
	str = ctime(&current_time);
	now = time(0);
	write(1, str + 4, 7);
	if ((now - current_time) <= SIX_MONTHS)
		write(1, str + 11, 5);
	else
	{
		write(1, " ", 1);
		write(1, str + 20, 4);
	}
	write(1, " ", 1);
}

void	print_long_file_info(t_f_node *node, t_input input) //
{
	long		time;

	if (input.flags & A || node->hidden == 0)
	{
		print_file_type(node);
		print_permissions(node);
		ft_putchar(' ');
//		ft_printf("%4d", node->hlink);
//		if (!(input.flags & G))
//			ft_printf("%s", node->username);
//		ft_printf("%s", node->groupname);
		if (node->filetype & BLOCK_DEVICE || node->filetype & CHARACTER_DEVICE)
		{
		//	printf("Major: %d\n", node->major);
		//	ft_printf("Minor: %d\n", node->minor);
		}
		else
//		ft_printf("%d\n", node->size);
		print_last_mod(node);
		print_filename(node, input);
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

int		get_stat_info(t_info *current, char *f_name, char *path, t_input *input)
{
	struct stat		buf;
	char			*temp;

	if (lstat(f_name, &buf) == -1)
	{
		temp = file_to_path(path, current->f_name);
		if (lstat(temp, &buf) == -1)
			return (0);
	}
	if (current->filetype & BLOCK_DEVICE || current->filetype & CHARACTER_DEVICE)
	{
		current->major = major(buf.st_rdev);
		current->minor = minor(buf.st_rdev);
	}
	fill_permissions(current, buf.st_mode);
	current->hlink = buf.st_nlink;
	current->size = buf.st_size;
	if (current->hidden == 0 || input->show_hidden)
		input->size += buf.st_blocks;
	current->uid = buf.st_uid;
	current->gid = buf.st_gid;
	return (1);
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

int		get_sort_info(t_info *current, char *path) //
{
	struct stat		buf;
	char			*temp;

	if (lstat(current->f_name, &buf) == -1)
	{
		temp = file_to_path(path, current->f_name);
		lstat(temp, &buf);
		free(temp);
	}
	fill_file_type(current, buf);
	current->last_modified = buf.st_mtimespec;
	current->last_accessed = buf.st_atimespec;
	current->hidden = current->f_name[0] == '.' ? 1 : 0;
	return (1);
}

t_q_link	*create_link(char *str, t_info current)
{
	t_q_link	*new;

	new = malloc(sizeof(t_q_link));
	new->directory = ft_strdup(str);
	new->info = current;
	new->next = 0;
	return (new);
}

void		push_queue(char *name, t_q_link **head, t_info current)
{
	t_q_link	*link;

	if (!(*head))
	{
		*head = create_link(name, current);
		return ;
	}
	link = *head;
	while (link->next)
		link = link->next;
	link->next = create_link(name, current);
}

t_q_link		*pop_queue(t_q_link **head)
{
	t_q_link	*temp;
	t_q_link	*other_temp;

	temp = *head;
	if (!(temp->next))
	{
		temp = *head;
		*head = 0;
	}
	else if (temp->next->next == 0)
	{
		temp = temp->next;
		(*head)->next = 0;
	}
	else
	{
		while (temp->next->next)
			temp = temp->next;
		other_temp = temp;
		temp = temp->next;
		other_temp->next = 0;
	}
	return (temp);
}

t_q_link		*unshift_queue(t_q_link **head)
{
	t_q_link	*temp;

	temp = *head;
	*head = (*head)->next;
	return (temp);
}

int		recurse_me(char *directory, t_input input)
{
	if (input.show_hidden || directory[0] != '.')
	{
		if (ft_strcmp(directory, ".") == 0 || ft_strcmp(directory, "..") == 0)
			return (0);
		return (1);
	}
	return (0);
}

void		reset_t_info(t_info *current)
{
	//current->last_modified = 0;
	current->filetype = 0;
	current->groupname = 0;
	current->username = 0;
	current->f_name = 0;
	current->permissions = 0;
	current->hidden = 0;
	current->hlink = 0;
 	current->size = 0;
 	current->uid = 0;
 	current->gid = 0;
}

void			fill_dequeue_function(t_input *input)
{
	if (input->flags & R)
		input->dequeue = pop_queue;
	else
		input->dequeue = unshift_queue;
}

void		get_long_info(t_info *current, char *directory_name, t_input *input)
{
			get_stat_info(current, current->f_name, directory_name, input);
//			get_owner_info(&current);
			get_group_info(current);
}

void		get_file_info(t_info *current, t_input *input,
		struct dirent *file, char *directory_name)
{
	reset_t_info(current);
	current->f_name = ft_strdup(file->d_name);
	get_sort_info(current, directory_name);
	if (input->flags & L)
		get_long_info(current, directory_name, input);
}

void		handle_queue(t_q_link **queue, char *directory_name, t_input *input)
{
	t_q_link		*tmp;

	tmp = input->dequeue(queue);
	tmp->directory = file_to_path(directory_name, tmp->directory);
	get_directory(tmp->directory, input, tmp->info, 0);
	free(tmp->directory);
	free(tmp);
}

int			get_directory(char *directory_name, t_input *input, t_info current, int first)
{
	struct dirent	*file;
	t_f_node		*head;
	t_q_link		*queue;
	DIR				*directory;

	head = 0;
	queue = 0;
	directory = opendir(directory_name);
	if (!first)
	{
		write(1, "\n", 1);
		write(1, directory_name, ft_strlen(directory_name));
		write(1, ":\n", 2);
	}
	while ((file = readdir(directory)))
	{
		get_file_info(&current, input, file, directory_name);
		insert_node(&head, current, input->sort);
		if (input->flags & CR && current.filetype & DIRECTORY && recurse_me(file->d_name, *input))
			push_queue(file->d_name, &queue, current);
	}
	(void)closedir(directory);
//	if (input->flags & L)
//		ft_printf("total %d\n", input->size);
	input->for_each_node(head, *input, input->file_print);
	while (input->flags & CR && queue)
		handle_queue(&queue, directory_name, input);
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
//	free(head->username);
//	free(head->groupname);
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
	else if (c == 'y')
		input->flags = input->flags | Y;
	else if (c == 'z')
		input->flags = input->flags | Z;
	else
	{
		ft_putstr("usage: ft_ls [-Radfglrtuy] [file ...]\n");
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

t_in_file	*create_in_file_node(char *path, int is_dir)
{
	t_in_file	*elem;

	elem = malloc(sizeof(t_in_file));
	elem->path = ft_strdup(path);
	elem->is_directory = is_dir;
	elem->next = 0;
	elem->error = 0;
	return (elem);
}

void	push_input_file(t_in_file **head, char *path, int is_dir)
{
	t_in_file	*temp;

	temp = *head;
	if (!temp)
	{
		*head = create_in_file_node(path, is_dir);
		check_exists(*head);
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = create_in_file_node(path, is_dir);
		check_exists(temp->next);
	}
}

int			files_first_alpha(t_in_file *n1, t_in_file *n2)
{
	//returning one if I want the second one first for now..
	if (n1->is_directory)
	{
		if (n2->is_directory)
			return (sort_alpha(n1->path, n2->path));
		else
			return (1);
	}
	if (n2->is_directory)
		return (0);
	else
		return (sort_alpha(n1->path, n2->path));
}

void	swap_head(t_in_file **head)
{
	t_in_file	*elem;
	t_in_file	*temp;

	*head = elem->next;
	temp = (*head)->next;
	(*head)->next = elem;
	elem->next = temp;
	elem = *head;
}

int		bubble_sort_input(t_in_file **head, int (*f)(t_in_file *n1, t_in_file *n2))
{
	t_in_file	*other_temp;
	t_in_file	*temp;
	t_in_file	*elem;
	int			complete;
	int			result;

	complete = 0;
	result = 1;
	elem = *head;
	while (!complete)
	{
		complete = 1;
		if (f(*head, (*head)->next))
			swap_head(head);
		while (elem->next->next)
		{
			if (is_directory(elem->path) || is_directory(elem->next->path))
				result = 0;
			if (f(elem->next, elem->next->next))
			{
				complete = 0;
				temp = elem->next->next->next;
				other_temp = elem->next;
				elem->next = elem->next->next;
				elem->next->next = other_temp;
				elem->next->next->next = temp;
			}
			elem = elem->next;
		}
		elem = *head;
		if (is_directory(elem->next->path))
			result = 0;
	}
	return (result);
}

int		sort_input(t_in_file **head, int (*f)(t_in_file *n1, t_in_file *n2))
{
	t_in_file	*elem;
	t_in_file	*temp;

	if (*head == 0 || (*head)->next == 0)
		return (1);
	elem = *head;
	if (f(elem, elem->next))
		swap_head(head);
/*	while (!complete)
	{
		if (is_directory(elem->path) || is_directory(elem->next->path))
			result = 0;
		complete = 1;
		while (elem->next->next)
		{
			if (f(elem->next, elem->next->next))
			{
				printf("sorting\n");
				if (is_directory(elem->path))
					result = 0;
				complete = 0;
				other_temp = elem->next->next->next;
				temp = elem->next;
				elem->next = elem->next->next;
				elem->next->next = temp;
				elem->next->next = other_temp;
			}
			elem = elem->next;
		}
		if (is_directory(elem->next->path))
			result = 0;
	}
*/	return (bubble_sort_input(head, f));
}

void		get_input_info(t_input *input, int argc, char **argv) //
{
	int			i;

	//f flag overwrites t.
	i = 1;
	while (i < argc && parse_flag(input, argv[i]))
		i++;
	overwrite_flags(input);
	input->directories = 0;
	if (i < argc)
	{
		while (i < argc)
		{
			push_input_file(&(input->directories), argv[i], is_directory(argv[i]));
			i++;
		}
	}
	else
		push_input_file(&(input->directories), ".", 1);
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
	else if (input->flags & U)
		input->sort = sort_accessed;
	else if (input->flags & Y)
		input->sort = sort_directories_first_node;
	else if (input->flags & Z)
		input->sort = sort_length_node;
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

/*void		get_file_info(t_info *current, t_input *input,
		struct dirent *file, char * directory_name)
{
	reset_t_info(current);
	current->f_name = ft_strdup(file->d_name);
	get_sort_info(current, directory_name);
	if (input->flags & L)
		get_long_info(current, directory_name);
}*/

//	../../PHP/day02/ex01/one_more_time.php

void	print_single_file(char *path, t_input input)
{
	struct stat	details;
	t_f_node	*head;
	t_info		current;

	if (input.flags & L)
	{
		//Here, we need to see if this file exists and get all of its information.
		head = 0;
		current.f_name = ft_strdup(path);
		get_sort_info(&current, path);
		get_stat_info(&current, path, "00", &input);
		get_owner_info(&current);
		get_group_info(&current);
		insert_node(&head, current, input.sort);
		input.for_each_node(head, input, input.file_print);
		free_tree(head);
	}
	else
		ft_putendl(path);
}

void	free_input(t_in_file *file)
{
	if (file->next)
		free_input(file->next);
	free(file->path);
	free(file);
}

void	print_no_rights_err(t_in_file *head)
{
	struct dirent	*file;
	t_in_file		*elem;
	DIR				*directory;


	elem = head;
	while (elem)
	{
		if (elem->error == 13)
		{
			directory = opendir(elem->path);
			write(1, "ft_ls: ", 7);
			write(1, elem->path, ft_strlen(elem->path));
			write(1, ": ", 2);
			perror(0);
		}
		elem = elem->next;
	}
}

void	print_no_exists_err(t_in_file *head)
{
	t_in_file	*elem;
	struct stat	details;

	elem = head;
	while (elem)
	{
		if (elem->error == 2)
		{
			stat(elem->path, &details);
			write(1, "ft_ls: ", 7);
			write(1, elem->path, ft_strlen(elem->path));
			write(1, ": ", 2);
			perror(0);
		}
		elem = elem->next;
	}
}

int		main(int argc, char **argv)
{
	t_in_file	*elem;
	t_input		input;
	t_info		current;
	int			result;
	int			i;

	get_input_info(&input, argc, argv);
	i = 0;
	assign_sorting_function(&input);
	assign_traversal_function(&input);
	assign_print_function(&input);
	input.show_hidden = input.flags & A ? 1 : 0;
	fill_dequeue_function(&input);
	result = sort_input(&(input.directories), files_first_alpha);
	elem = input.directories;
	input.size = 0;
	print_no_exists_err(elem);
	while (elem)
	{
		if (is_directory(elem->path) && !(input.flags & D) && !(elem->error))
			get_directory(elem->path, &input, current, result);
		else if (!(elem->error))
			print_single_file(elem->path, input);
		elem = elem->next;
	}
	print_no_rights_err(input.directories);
	free_input(input.directories);
	return (0);
}
