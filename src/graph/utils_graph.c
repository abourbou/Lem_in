/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:31:24 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/24 13:18:49 by abourbou         ###   ########lyon.fr   */
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

// Find nodes for edge and put them inside first_node and second_node
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
void	create_link(t_node *node1, t_node *node2)
{
	t_link	*link;
	t_link	*reverse_link;

	link = malloc(sizeof(t_link));
	reverse_link = malloc(sizeof(t_link));
	link->flow = 1;
	reverse_link->flow = 1;
	link->terminal = node2;
	reverse_link->terminal = node1;
	dlist_pushback(&node1->l_links, dlist_new(link));
	dlist_pushback(&node2->l_links, dlist_new(reverse_link));
}
