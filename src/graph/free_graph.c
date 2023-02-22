/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:17:25 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/24 13:23:28 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	free_node(t_node *node)
{
	t_dlist	*current_llinks;
	t_dlist	*next_llinks;

	free_if_not_empty(node->name);
	current_llinks = node->l_links;
	while (current_llinks)
	{
		next_llinks = current_llinks->next;
		free_if_not_empty(current_llinks->content);
		free(current_llinks);
		current_llinks = next_llinks;
	}
	free(node);
}

void	free_graph(t_graph *graph)
{
	t_dlist	*current_lnode;
	t_dlist	*next_lnode;
	t_node	*node;

	graph->source = 0;
	graph->sink = 0;
	current_lnode = graph->lnode;
	while (current_lnode)
	{
		next_lnode = current_lnode->next;
		node = current_lnode->content;
		if (node)
			free_node(node);
		free(current_lnode);
		current_lnode = next_lnode;
	}
}
