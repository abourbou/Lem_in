/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:18:05 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/02 22:00:48 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

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

// Create links for unique room
// room1 <-> room2 <=>
// room1 [in]  -> room1 [out]
// room1 [out] -> room2 [in]
// room2 [in]  -> room2 [out]
// room2[out]  -> room1[in]
// Except Start and End
short	create_unique_room_link(t_graph *graph, t_node *node1, t_node *node2)
{
	if (!node1->node_out)
	{
		if (create_node_out(node1))
			return (EXIT_FAILURE);
		if (create_link(node1, node1->node_out))
			return (EXIT_FAILURE);
	}
	if (!node2->node_out)
	{
		if (create_node_out(node2))
			return (EXIT_FAILURE);
		if (create_link(node2, node2->node_out))
			return (EXIT_FAILURE);
	}
	if (node2 != graph->start_node && node1 != graph->end_node)
	{
		if (create_link(node1->node_out, node2))
			return (EXIT_FAILURE);
	}
	if (node1 != graph->start_node && node2 != graph->end_node)
		if (create_link(node2->node_out, node1))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
