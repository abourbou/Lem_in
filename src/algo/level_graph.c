/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:54:29 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/27 17:18:24 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

void	reset_level_graph(t_graph *graph)
{
	t_dlist	*current_lnode;
	t_node	*node;

	current_lnode = graph->l_node;
	while (current_lnode)
	{
		node = current_lnode->content;
		node->level = MAX_UNSIGN_INT;
		node->is_used = false;
		current_lnode = current_lnode->next;
	}
}

short	create_queue_node(t_queue *queue, t_node *node)
{
	queue->start = 0;
	queue->end = 0;
	if (queue_push(queue, node))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_node	*examinate_level(t_node *prev_node, t_link *link)
{
	t_node	*node;

	node = find_opposite_node(link, prev_node);
	if (node->is_used || node->level <= prev_node->level
		|| can_access_node(link, node))
		return (0);
	return (node);
}

short	propagate_level(t_queue *queue_node, t_node *node, t_node *end)
{
	t_dlist	*current_llink;
	t_node	*opposite_node;

	current_llink = node->l_links;
	while (current_llink)
	{
		opposite_node = examinate_level(node, current_llink->content);
		if (opposite_node)
		{
			opposite_node->level = node->level + 1;
			if (opposite_node != end)
			{
				if (queue_push(queue_node, opposite_node))
				{
					free_queue(queue_node, 0);
					return (-1);
				}
			}
		}
		current_llink = current_llink->next;
	}
	return (0);
}

int	construct_level_graph(t_graph *graph)
{
	t_queue	queue_node;
	t_node	*node;

	reset_level_graph(graph);
	graph->start_node->level = 0;
	create_queue_node(&queue_node, graph->start_node);
	while (!is_queue_empty(&queue_node))
	{
		node = queue_pop(&queue_node);
		node->is_used = true;
		if (propagate_level(&queue_node, node, graph->end_node) == -1)
		{
			print_error("can not malloc in construct_level_graph");
			free_graph(graph);
			exit(1);
		}
	}
	if (graph->end_node->level == MAX_UNSIGN_INT)
		return (1);
	return (0);
}
