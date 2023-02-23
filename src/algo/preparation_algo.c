/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation_algo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:59:45 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/23 11:22:37 by abourbou         ###   ########lyon.fr   */
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

void	erase_useless_nodes(t_graph *graph)
{
	(void)graph;
}