/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation_algo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:59:45 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/23 16:52:17 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

short DFS_find_end(t_node *node, t_node *end)
{
	t_dlist *current;
	t_link *link;

	// printf("in node : %s\n", node->name);
	if (node == end)
		return (EXIT_SUCCESS);
	if (node->is_used)
		return (EXIT_FAILURE);
	node->is_used = true;
	current = node->l_links;
	while (current)
	{
		link = current->content;
		// printf("link to %s : %s\n", node->name, link->terminal->name);
		if (!DFS_find_end(link->terminal, end))
			return (EXIT_SUCCESS);
		current = current->next;
	}
	return (EXIT_FAILURE);
}

short	check_path_exists(t_graph *graph)
{
	t_dlist *lcurrent;
	t_node *node;

	lcurrent = graph->lnode;
	while (lcurrent)
	{
		node = lcurrent->content;
		node->is_used = false;
		lcurrent = lcurrent->next;
	}

	return (DFS_find_end(graph->source, graph->sink));
}

/**
 * Erase nodes that have less than 2 connections
 * because they will never be usefull for the graph
*/
void	erase_dead_end_nodes(t_graph *graph)
{
	short	is_change;
	t_dlist	*lnode;
	t_node	*node;

	is_change = true;
	while (is_change)
	{
		is_change = false;
		lnode = graph->lnode;
		while (lnode)
		{
			node = lnode->content;
			if (node != graph->source && node != graph->sink
				&& dlist_compt(node->l_links) < 2)
			{
				erase_node(node);
				dlist_erase(&graph->lnode, lnode);
				is_change = true;
			}
			lnode = lnode->next;
		}
	}
}