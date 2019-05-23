/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 07:09:01 by chford            #+#    #+#             */
/*   Updated: 2019/05/23 07:21:14 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_ls.h"

void print2DUtil(t_f_node *root, int space) 
{ 
    if (root == NULL) 
        return; 
  
    space += 10; 
  
    print2DUtil(root->right, space); 
  
    printf("\n"); 
    for (int i = 10; i < space; i++) 
        printf(" "); 
    printf("%s\n", root->f_name); 
  
    print2DUtil(root->left, space); 
} 
  
void print2D(t_f_node *root) 
{ 
   print2DUtil(root, 0); 
} 
