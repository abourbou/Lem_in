/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:31:24 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/24 17:52:46 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

t_node	*convert_vertex_to_node(t_vertex *vertex)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->name = ft_strdup(vertex->name);
	node->l_links = 0;
	node->is_used = false;
	node->dist_source = 4294967295;
	node->ant_nb = 0;
	return (node);
}

// Find nodes from edge and put them inside first_node and second_node
short	find_nodes(t_edge *edge, t_graph *graph, t_node **first_node,
												t_node **second_node)
{
	t_dlist	*current_lnode;
	t_node	*node;

	current_lnode = graph->lnode;
	*first_node = 0;
	*second_node = 0;
	while (current_lnode && (!*first_node || !*second_node))
	{
		node = current_lnode->content;
		if (!*first_node && !ft_strcmp(node->name, edge->vertex1))
			*first_node = current_lnode->content;
		else if (!*second_node && !ft_strcmp(node->name, edge->vertex2))
			*second_node = current_lnode->content;
		current_lnode = current_lnode->next;
	}
	if (!current_lnode && (!*first_node || !*second_node))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// Create a link in both direction
short	create_link(t_node *node1, t_node *node2)
{
	t_link	*link;

	link = malloc(sizeof(t_link));
	if (!link)
		return (EXIT_FAILURE);
	link->flow = 0;
	link->node1 = node1;
	link->node2 = node2;
	dlist_pushfront(&node1->l_links, dlist_new(link));
	dlist_pushfront(&node2->l_links, dlist_new(link));
	return (EXIT_SUCCESS);
}

// Check if a link already exist between node1 and node2
short	check_link_already_exist(t_node *node1, t_node *node2)
{
	t_dlist	*current_llink;
	t_link	*link;

	current_llink = node1->l_links;
	while (current_llink)
	{
		link = current_llink->content;
		if (link->node1 == node2 || link->node2 == node2)
			return (EXIT_FAILURE);
		current_llink = current_llink->next;
	}
	return (EXIT_SUCCESS);
}

// Find the opposite node of a link based on the first one
t_node	*find_opposite_node(t_link *link, t_node *tail)
{
	if (link->node1 == tail)
		return (link->node2);
	else if (link->node2 == tail)
		return (link->node1);
	return (0);
}
