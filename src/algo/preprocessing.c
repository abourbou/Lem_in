/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:59:45 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/01 18:03:33 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

// DFS algorithm saying if end can be reach from node
short	dfs_find_end(t_node *node, t_node *end)
{
	t_dlist	*current;
	t_link	*link;
	t_node	*opposite_node;

	if (node == end)
		return (EXIT_SUCCESS);
	if (node->is_used)
		return (EXIT_FAILURE);
	node->is_used = true;
	current = node->l_links;
	while (current)
	{
		link = current->content;
		opposite_node = find_opposite_node(link, node);
		if (!dfs_find_end(opposite_node, end))
			return (EXIT_SUCCESS);
		current = current->next;
	}
	return (EXIT_FAILURE);
}

short	check_path_exists(t_graph *graph)
{
	t_dlist	*lcurrent;
	t_node	*node;

	lcurrent = graph->l_node;
	while (lcurrent)
	{
		node = lcurrent->content;
		node->is_used = false;
		lcurrent = lcurrent->next;
	}
	return (dfs_find_end(graph->start_node, graph->end_node));
}

/**
 * Erase nodes that have less than 2 connections
 * because they will never be usefull for the graph
*/
void	erase_dead_end_nodes(t_graph *graph)
{
	short	is_change;
	t_dlist	*lnode_next;
	t_dlist	*l_node;
	t_node	*node;

	is_change = true;
	while (is_change)
	{
		is_change = false;
		l_node = graph->l_node;
		while (l_node)
		{
			lnode_next = l_node->next;
			node = l_node->content;
			if (node != graph->start_node && node != graph->end_node
				&& dlist_compt(node->l_links) < 2)
			{
				erase_node(node);
				dlist_erase(&graph->l_node, l_node);
				is_change = true;
			}
			l_node = lnode_next;
		}
	}
}
