/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_blocking_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 08:45:20 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/01 18:03:10 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

void	dlist_swap_content(t_dlist *first, t_dlist *second)
{
	void	*buffer;

	buffer = first->content;
	first->content = second->content;
	second->content = buffer;
}

// Sort links of the node by level
void	bubble_sort_level(t_dlist *start_llink, t_node *node, int swapped)
{
	t_dlist	*current_llink;
	t_dlist	*sorted_llink;
	t_node	*opp_node1;
	t_node	*opp_node2;

	sorted_llink = 0;
	while (swapped)
	{
		swapped = 0;
		current_llink = start_llink;
		while (current_llink->next != sorted_llink)
		{
			opp_node1 = find_opposite_node(current_llink->content, node);
			opp_node2 = find_opposite_node(current_llink->next->content, node);
			if (opp_node1->level > opp_node2->level)
			{
				dlist_swap_content(current_llink, current_llink->next);
				swapped = 1;
			}
			current_llink = current_llink->next;
		}
		sorted_llink = current_llink;
	}
}

short	increm_link(t_link *link, t_node *node, t_node *opp_node)
{
	increment_flow(link, opp_node, node);
	node->level = MAX_UNSIGN_INT;
	return (EXIT_SUCCESS);
}

short	dfs_augmenting_path(t_node *node, t_node *start, t_node *end)
{
	t_dlist	*llink;
	t_link	*link;
	t_node	*opp_node;

	// printf("dfs from %s\n", node->name);
	llink = node->l_links;
	while (llink)
	{
		link = llink->content;
		opp_node = find_opposite_node(link, node);
		// printf("l %s - %s, opp : %s\n", link->node1->name, link->node2->name, opp_node->name);
		if (opp_node == start)
		{
			// printf("Find a path! Flow : %lu | ", *flow);
			// printf("path : %s - %s - ", opp_node->name, node->name);
			return (increm_link(link, node, opp_node));
		}
		if (opp_node == end
			|| (node != end && opp_node->level != node->level - 1)
			|| can_access_residual_node(link, node))
		{
			// printf("pass\n");
			llink = llink->next;
			continue ;
		}
		if (!dfs_augmenting_path(opp_node, start, end))
		{
			// printf("%s - ", node->name);
			return (increm_link(link, node, opp_node));
		}
		llink = llink->next;
	}
	node->level = MAX_UNSIGN_INT;
	return (EXIT_FAILURE);
}

void	find_blocking_path(t_graph *graph, size_t *flow, size_t max_theor_flow)
{
	t_dlist	*llink_end;
	t_node	*opp_node;
	t_link	*link;

	bubble_sort_level(graph->end_node->l_links, graph->end_node, 1);
	llink_end = graph->end_node->l_links;
	while (llink_end && *flow < max_theor_flow)
	{
		link = llink_end->content;
		opp_node = find_opposite_node(link, graph->end_node);
		// printf("opp_node from end : %s\n", opp_node->name);
		if (!can_access_residual_node(link, graph->end_node)
			&& !dfs_augmenting_path(opp_node, graph->start_node,
				graph->end_node))
		{
			// printf("%s\n", graph->end_node->name);
			increment_flow(link, opp_node, graph->end_node);
			++*flow;
		}
		llink_end = llink_end->next;
	}
}
