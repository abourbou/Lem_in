/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:59:45 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/02 15:56:29 by abourbou         ###   ########lyon.fr   */
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
		if (link->node1 != node)
		{
			current = current->next;
			continue ;
		}
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
