/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 19:33:47 by chford            #+#    #+#             */
/*   Updated: 2019/05/19 18:17:58 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int		sort_alpha_node(t_f_node *n1, t_info n2)
{
	int		i;

	i = 0;
	while ((n1->f_name)[i] == n2.f_name[i] && (n1->f_name)[i] != '\0')
		i++;
	if ((n1->f_name)[i] < n2.f_name[i])
		return (0);
	return (1);
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
	if ((*grand)->left->right)
		(*grand)->left = left_rotate((*grand)->left);
	*grand = right_rotate(*grand);
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
	{
		handle_left_tree_inbalance(orig);
		printf("after handling the left tree inbalance, the structof the tree looks like this:\n");
		printf("          %s\n",(*orig)->f_name);
		printf("%s                  %s\n",(*orig)->left->f_name, (*orig)->right->f_name);
	}
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
		insert_node(head, current, sort_alpha_node);
	}
	(void)closedir(directory);
	return (1);
}

int		main(int argc, char **argv)
{
	t_f_node	*head;
	head = 0;
	if (argc == 1)
	{
		get_directory(".", &head);
		inorder_traversal_apply(head, print_filename); 
		printf("\n\n\n%d\n", get_max_length_node(head));
		printf("\n%s\n", head->left->right->f_name);
		printf("\n%s\n", head->left->right->left->f_name);
		printf("\n%s\n", head->left->right->right->f_name);
	}
	return (0);
}
