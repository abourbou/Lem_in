/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:02:50 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/24 12:25:15 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static t_btnode	*new_node(char *name)
{
	t_btnode	*new_node;

	new_node = ft_calloc(1, sizeof(t_btnode));
	new_node->name = ft_strdup(name);
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_btnode	*add_node(t_btnode *node, char *name)
{
	if (node == NULL)
		return (new_node(name));
	if (ft_strcmp(name, node->name) < 0)
		node->left = add_node(node->left, name);
	else if (ft_strcmp(name, node->name) > 0)
		node->right = add_node(node->right, name);
	return (node);
}

bool	is_exist(t_btnode *node, char *name)
{
	int		som;

	if (node == NULL)
		return (false);
	som = ft_strcmp(node->name, name);
	if (som == 0)
		return (true);
	else if (som > 0)
		return (is_exist(node->left, name));
	else
		return (is_exist(node->right, name));
}

void	free_dico_vertex(t_btnode *node)
{
	if (node == NULL)
		return ;
	free(node->name);
	free_dico_vertex(node->left);
	free_dico_vertex(node->right);
	free(node);
}
