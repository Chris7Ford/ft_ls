/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:50:29 by chford            #+#    #+#             */
/*   Updated: 2019/06/05 07:20:08 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	int		ret;

	i = 0;
	while ((n1->f_name)[i] == n2.f_name[i] && (n1->f_name)[i] != '\0')
		i++;
	if (ft_isalnum(n1->f_name[i]) == 0 && n1->f_name[i] != '.' && ft_isupper(n2.f_name[i]))
		ret = 1;
	else if (ft_isalnum(n1->f_name[i]) == 0 && n1->f_name[i] != '.' && ft_islower(n2.f_name[i]))
		ret = 0;
	else if (ft_isalnum(n2.f_name[i]) == 0 && n2.f_name[i] != '.' && ft_isupper(n1->f_name[i]))
		ret = 0;
	else if (ft_isalnum(n2.f_name[i]) == 0 && n2.f_name[i] != '.' && ft_islower(n1->f_name[i]))
		ret = 1;
	else
		ret =  (!((n1->f_name)[i] < n2.f_name[i]));
	return (ret);
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

int		sort_nanosec(long nsec1, long nsec2)
{
	return (nsec1 < nsec2);
}

int		sort_accessed(t_f_node *n1, t_info n2)
{
	if (n1->last_accessed.tv_sec == n2.last_accessed.tv_sec)
	{
		if (!(n1->last_accessed.tv_nsec == n2.last_accessed.tv_nsec))
			return (sort_nanosec(n1->last_accessed.tv_nsec, n2.last_accessed.tv_nsec));
		return (sort_alpha_node(n1, n2));
	}
	return (n1->last_accessed.tv_sec < n2.last_accessed.tv_sec);
}

int		sort_modified(t_f_node *n1, t_info n2)
{
	if (n1->last_modified.tv_sec == n2.last_modified.tv_sec)
	{
		if (!(n1->last_modified.tv_nsec == n2.last_modified.tv_nsec))
			return (sort_nanosec(n1->last_modified.tv_nsec, n2.last_modified.tv_nsec));
		return (sort_alpha_node(n1, n2));
	}
	return (n1->last_modified.tv_sec < n2.last_modified.tv_sec);
}

int		do_not_sort(t_f_node *n1, t_info n2)
{
	if ((ft_strcmp(n2.f_name, ".") == 0 /*&& ft_strcmp(n2.f_name, "..")) */) ||
			(ft_strcmp(n2.f_name, "..") == 0 && ft_strcmp(n1->f_name, ".")))
				return (1);
	return (0);
}

void	print_link_file(t_f_node *node, char *path)
{
	char	*temp;
	char	buffer[4097];
	int		count;

	temp = file_to_path(path, node->f_name);
	count = readlink(temp, buffer, sizeof(buffer));
	if (count >= 0)
	{
		buffer[count] = '\0';
		write(1, " -> ", 4);
		write(1, buffer, ft_strlen(buffer));
	}
	free(temp);
}

void	print_filename(t_f_node *node, t_input input, char *path)
{
	if (input.show_hidden || !(node->hidden))
	{
		write(1, node->f_name, ft_strlen(node->f_name));
		if (node->is_link && input.flags & _L)
			print_link_file(node, path);
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

void	inorder_traversal_apply(t_f_node *elem, t_input input, t_q_link **queue, char *path)
{
	if (elem->left)
		inorder_traversal_apply(elem->left, input, queue, path);
	input.file_print(elem, input, path);
	if (input.flags & _CR && elem->filetype & DIRECTORY && recurse_me(elem->f_name, input))
		//This function will have to change to get the information from the node, not current...
		push_queue(elem->f_name, queue);
	if (elem->right)
		inorder_traversal_apply(elem->right, input, queue, path);
}

void	reverse_inorder_traversal_apply(t_f_node *elem, t_input input, t_q_link **queue, char *path)
{
	if (elem->right)
		reverse_inorder_traversal_apply(elem->right, input, queue, path);
	input.file_print(elem, input, path);
	
	if (input.flags & _CR && elem->filetype & DIRECTORY && recurse_me(elem->f_name, input))
		//This function will have to change to get the information from the node, not current...
		push_queue(elem->f_name, queue);
	if (elem->left)
		reverse_inorder_traversal_apply(elem->left, input, queue, path);
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

void	print_long_file_info(t_f_node *node, t_input input, char *path)
{
	long		time;

	if (input.flags & _A || node->hidden == 0)
	{
		print_file_type(node);
		print_permissions(node);
		ft_printf("%3d ", node->hlink);
		if (!(input.flags & _G))
			ft_printf("%-7s", node->username);
		ft_printf(" %s", node->groupname);
		if (node->filetype & BLOCK_DEVICE || node->filetype & CHARACTER_DEVICE)
		{
			ft_printf(" %d,", node->major);
			ft_printf(" %d ", node->minor);
		}
		else
		ft_printf("%7d ", node->size);
		print_last_mod(node);
		print_filename(node, input, path);
	}
}

void	fill_file_type(t_info *current, struct stat buf)
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

int		get_stat_info(t_info *current, char *f_name, char *path, t_input *input, int first)
{
	struct stat		buf;
	char			*temp;

	if (lstat(f_name, &buf) == -1 || !first)
//	if (!first)
	{
		temp = file_to_path(path, current->f_name);
		if (lstat(temp, &buf) == -1)
			return (0);
	}
//	else if (lstat(f_name, &buf) == -1)
//		return (0);
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

void	get_owner_info(t_info *current)
{
	struct passwd	*pwd;

	pwd = getpwuid(current->uid);
	if (pwd == 0)
		current->username = ft_itoa(current->uid);
	else
		current->username = ft_strdup(pwd->pw_name);
}

void	get_group_info(t_info *current)
{
	struct group	*grp;

	grp = getgrgid(current->gid);
	current->groupname = ft_strdup(grp->gr_name);
}

int		get_sort_info(t_info *current, char *path, int first)
{
	struct stat		buf;
	char			*temp;

	if (lstat(current->f_name, &buf) == -1 || !first)
	{
		temp = file_to_path(path, current->f_name);
		lstat(temp, &buf);
		free(temp);
	}
//	else
//		lstat(current->f_name, &buf);
	fill_file_type(current, buf);
	current->last_modified = buf.st_mtimespec;
	current->last_accessed = buf.st_atimespec;
	current->hidden = current->f_name[0] == '.' ? 1 : 0;
	return (1);
}

t_q_link	*create_link(char *str)
{
	t_q_link	*new;

	new = malloc(sizeof(t_q_link));
	new->directory = ft_strdup(str);
//	new->info = current;
	new->next = 0;
	return (new);
}

void		push_queue(char *name, t_q_link **head)
{
	t_q_link	*link;

	if (!(*head))
	{
//		*head = create_link(name, current);
		*head = create_link(name);
		return ;
	}
	link = *head;
	while (link->next)
		link = link->next;
//	link->next = create_link(name, current);
	link->next = create_link(name);
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

void		get_long_info(t_info *current, char *directory_name, t_input *input, int first)
{	
	get_stat_info(current, current->f_name, directory_name, input, first);
	get_owner_info(current);
	get_group_info(current);
}

void		get_file_info(t_info *current, t_input *input, char *directory_name, char *filename, int first)
{
	reset_t_info(current);
	current->f_name = ft_strdup(filename);
	get_sort_info(current, directory_name, first);
	if (input->flags & _L)
		get_long_info(current, directory_name, input, first);
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

void		print_directory_name(char *directory_name)
{
	write(1, "\n", 1);
	write(1, directory_name, ft_strlen(directory_name));
	write(1, ":\n", 2);
}

int			filter_directory_queue(t_q_link *n1, t_q_link *n2)
{
	char	*s1;
	char	*s2;
	int		i;

	s1 = n1->directory;
	s2 = n2->directory;
	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	if (ft_isalpha(s1[i]) == 0 && s1[i] != '.' && ft_isalpha(s2[i]))
		return (1);
	else if (ft_isalpha(s2[i]) == 0 && s2[i] != '.' && ft_isalpha(s1[i]))
		return (0);
	return (!((s1[i] < s2[i])));
	
}

int		swap_queue_head(t_q_link **head)
{
	t_q_link	*elem;
	t_q_link	*temp;

	*head = elem->next;
	temp = (*head)->next;
	(*head)->next = elem;
	elem->next = temp;
	elem = *head;
	return (1);
}

/*void		sort_queue(t_q_link **head, int (*f)(t_q_link *n1, t_q_link *n2))
{
	t_q_link	*elem;
	t_q_link	*temp;
	t_q_link	*other_temp;
	int			complete;

	if (!(*head) || !((*head)->next))
		return ;
	while ((!complete) && (complete = 1))
	{
		if ((f(*head, (*head)->next) && swap_queue_head(head)) || 1)
			elem = *head;
		while (elem->next->next)
		{
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
	}
}
*/
void		free_in_file(t_in_file *head)
{
	if (!head)
		return ;
	if (head->next)
		free_in_file(head->next);
	free(head);
}

void		init_get_directory(t_f_node **head, t_q_link **queue, t_input *input)
{
	*head = 0;
	*queue = 0;
	input->size = 0;
}

void		get_directory(char *directory_name, t_input *input, t_info current, int first)
{
	struct dirent	*file;
	t_f_node		*head;
	t_q_link		*queue;
	DIR				*directory;

	init_get_directory(&head, &queue, input);
	directory = opendir(directory_name);
	if (!directory)
	{
		print_no_rights_err_str(directory_name, 1);
		return ;
	}
	first ? 0 : print_directory_name(directory_name);
	while ((file = readdir(directory)))
	{
//		if (!first && (ft_strcmp(file->d_name, ".") == 0 || ft_strcmp(file->d_name, "..") == 0))
//			get_correct_file_from_dot(file->d_name, directory_name, input);
			///Working here. I want to replace . or .. with the correct directory from each recursion call. I need to pass the right path into stat instead of . or .., but keep . or .. as the filename
		get_file_info(&current, input, directory_name, file->d_name, first);
		insert_node(&head, current, input->sort);
	}
	(void)closedir(directory);
	input->flags & _L ? ft_printf("total %d\n", input->size) : 0;
	input->for_each_node(head, *input, &queue, directory_name);
	free_tree(head);
	//I think sort queue can go altogether
//	sort_queue(&queue, filter_directory_queue);
	while (input->flags & _CR && queue)
		handle_queue(&queue, directory_name, input);
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

void	add_flag(t_input *input, char c)
{
	if (c == 'l')
		input->flags = input->flags | _L;
	else if (c == 'R')
		input->flags = input->flags | _CR;
	else if (c == 'a')
		input->flags = input->flags | _A;
	else if (c == 'r')
		input->flags = input->flags | _R;
	else if (c == 't')
		input->flags = input->flags | _T;
	else if (c == 'u')
		input->flags = input->flags | _U;
	else if (c == 'f')
		input->flags = input->flags | _F;
	else if (c == 'g')
		input->flags = input->flags | _G;
	else if (c == 'd')
		input->flags = input->flags | _D;
	else if (c == 'y')
		input->flags = input->flags | _Y;
	else if (c == 'z')
		input->flags = input->flags | _Z;
	else
	{
		ft_putstr("usage: ft_ls [-Radfglrtuy] [file ...]\n");
		exit(0);
	}
}

int		parse_flag(t_input *input, char *str)
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

void	overwrite_ls_flags(t_input *input)
{
	if (input->flags & _F && input->flags & _T)
		input->flags -= _T;
	if (input->flags & _F)
	{
		input->flags |= _A;
		if (input->flags & _R)
			input->flags -= _R;
	}
}

t_in_file	*create_in_file_node(char *path, int is_dir, int pd)
{
	t_in_file	*elem;

	elem = malloc(sizeof(t_in_file));
	elem->path = ft_strdup(path);
	elem->is_directory = is_dir;
	elem->next = 0;
	elem->error = 0;
	elem->pd = pd;
	return (elem);
}

int		push_input_file(t_in_file **head, char *path, int is_dir, int pd)
{
	t_in_file	*temp;

	temp = *head;
	if (!temp)
	{
		*head = create_in_file_node(path, is_dir, pd);
		check_exists(*head);
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = create_in_file_node(path, is_dir, pd);
		check_exists(temp->next);
	}
	return (1);
}

int			files_first_alpha(t_in_file *n1, t_in_file *n2)
{
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

void	swap_input_head(t_in_file **head)
{
	t_in_file	*elem;
	t_in_file	*temp;

	*head = elem->next;
	temp = (*head)->next;
	(*head)->next = elem;
	elem->next = temp;
	elem = *head;
}

void	swap_input_links(t_in_file *elem, int *complete)
{
	t_in_file	*other_temp;
	t_in_file	*temp;

	*complete = 0;
	temp = elem->next->next->next;
	other_temp = elem->next;
	elem->next = elem->next->next;
	elem->next->next = other_temp;
	elem->next->next->next = temp;
}

int		bubble_sort_input(t_in_file **head, int (*f)(t_in_file *n1, t_in_file *n2))
{
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
			swap_input_head(head);
		while (elem->next->next)
		{
			if (is_directory(elem->path) || is_directory(elem->next->path))
				result = 0;
			if (f(elem->next, elem->next->next))
				swap_input_links(elem, &complete);
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
		swap_input_head(head);
	return (bubble_sort_input(head, f));
}

void		get_input_info(t_input *input, int argc, char **argv)
{
	int			i;

	i = 1;
	input->flags = 0;
	while (i < argc && parse_flag(input, argv[i]))
		i++;
	overwrite_ls_flags(input);
	input->directories = 0;
	if (i < argc)
	{
		while (i < argc)
		{
			push_input_file(&(input->directories), argv[i],
					is_directory(argv[i]),
					argc - i > 1 ? 1 : 0);
			i++;
		}
	}
	else
		push_input_file(&(input->directories), ".", 1, 0);
}

void	assign_traversal_function(t_input *input)
{
	if (input->flags & _R)
		input->for_each_node = &reverse_inorder_traversal_apply;
	else
		input->for_each_node = &inorder_traversal_apply;
}

void	assign_sorting_function(t_input *input)
{
	if (input->flags & _T)
		input->sort = sort_modified;
	else if (input->flags & _F)
		input->sort = do_not_sort;
	else if (input->flags & _U)
		input->sort = sort_accessed;
	else if (input->flags & _Y)
		input->sort = sort_directories_first_node;
	else if (input->flags & _Z)
		input->sort = sort_length_node;
	else
		input->sort = sort_alpha_node;
}

void	assign_print_function(t_input *input)
{
	if (input->flags & _L)
		input->file_print = print_long_file_info;
	else
		input->file_print = print_filename;
}

void	free_queue(t_q_link *queue)
{
	if (queue->next)
		free_queue(queue->next);
	free(queue->directory);
	free(queue);
}

void	print_single_file(char *path, t_input input)
{
	struct stat	details;
	t_f_node	*head;
	t_q_link	*queue;
	t_info		current;

	if (input.flags & _L)
	{
		head = 0;
		queue = 0;
		current.f_name = ft_strdup(path);
		get_sort_info(&current, path, 1);
		get_stat_info(&current, path, "00", &input, 1);
		get_owner_info(&current);
		get_group_info(&current);
		insert_node(&head, current, input.sort);
		//input.for_each_node(head, input, input.file_print);
		input.for_each_node(head, input, &queue, path);

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

int		dont_print_error(char *str)
{
	if (ft_strcmp(str, "usr") == 0)
		return (1);
	return (0);
}


void	print_no_rights_err_str(char *path, int pd)
{
	char			**path_words;
	int				i;
	DIR				*directory;

	i = 0;
	path_words = ft_strsplit(path, '/');
	while (path_words[i])
		i++;
	directory = opendir(path);
	if ((i > 1 || ft_strcmp(path_words[i - 1], ".")) && errno == 13)
	{
		while (i > 1 && ft_strcmp(path_words[i - 1], ".") == 0)
			i--;
		if (dont_print_error(path_words[i - 1]))
			return ;
		write(1, "\n", 1);
		pd ? ft_printf("%s:\nft_ls: ", path) : 0;
		ft_printf("%s: ", path_words[i - 1]);
		perror(0);
	}
	free_string_array(&path_words);
}

void	print_no_rights_err_lst(t_in_file *head)
{
	t_in_file		*elem;
	char			**path_words;
	int				i;
	DIR				*directory;

	elem = head;
	while (elem && !(i = 0))
	{
		path_words = ft_strsplit(elem->path, '/');
		while (path_words[i])
			i++;
		directory = opendir(elem->path);
		if ((i > 1 || ft_strcmp(path_words[i - 1], ".")) && errno == 13)
		{
			while (i > 1 && ft_strcmp(path_words[i - 1], ".") == 0)
				i--;
			if (dont_print_error(path_words[i - 1]) && write(1, "\n", 1))
				return ;
			elem->pd ? ft_printf("%s:\n", elem->path) : 0;
			ft_printf("ft_ls: %s: ", path_words[i - 1]);
			perror(0);
		}
		free_string_array(&path_words);
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

void	init_input(t_input *input)
{
	assign_sorting_function(input);
	assign_traversal_function(input);
	assign_print_function(input);
	input->show_hidden = input->flags & _A ? 1 : 0;
	input->dequeue = unshift_queue;
	input->size = 0;
	input->local_err = 0;
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
	result = sort_input(&(input.directories), files_first_alpha);
	init_input(&input);
	elem = input.directories;
	print_no_exists_err(elem);
	while (elem)
	{
		if (is_directory(elem->path) && !(input.flags & _D) && !(elem->error))
			get_directory(elem->path, &input, current, result);
		else if (!(elem->error))
			print_single_file(elem->path, input);
		elem = elem->next;
	}
	elem = input.directories;
	print_no_rights_err_lst(elem);
	free_input(input.directories);
	return (0);
}
