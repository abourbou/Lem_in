/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:17:25 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/01 18:04:00 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	free_graph(t_graph *graph)
{
	t_dlist	*current_lnode;
	t_dlist	*next_lnode;
	t_node	*node;

	graph->start_node = 0;
	graph->end_node = 0;
	current_lnode = graph->l_node;
	while (current_lnode)
	{
		next_lnode = current_lnode->next;
		node = current_lnode->content;
		if (node)
			erase_node(node);
		free(current_lnode);
		current_lnode = next_lnode;
	}
}

// Find the list element of node containing link
void	*find_llink(t_link *link, t_node *node)
{
	t_dlist	*current_llink;

	current_llink = node->l_links;
	while (current_llink)
	{
		if (current_llink->content == link)
			return (current_llink);
		current_llink = current_llink->next;
	}
	return (0);
}

// Erase the node
// Erase the link in the list of the other nodes linked to him
// Erase the link and the list elem
void	erase_node(t_node *node)
{
	t_dlist	*current_llink;
	t_node	*other_node;
	t_dlist	*other_node_l_links;
	t_dlist	*next_llink;

	current_llink = node->l_links;
	while (current_llink)
	{
		next_llink = current_llink->next;
		other_node = find_opposite_node(current_llink->content, node);
		other_node_l_links = find_llink(current_llink->content, other_node);
		dlist_erase(&other_node->l_links, other_node_l_links);
		free(current_llink->content);
		free(current_llink);
		current_llink = next_llink;
	}
	free(node->name);
	free(node);
}
