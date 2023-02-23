/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:17:25 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/24 13:31:03 by abourbou         ###   ########lyon.fr   */
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

void	erase_node(t_node *node)
{
	t_dlist	*current;
	t_node *other_node;
	t_dlist *other_node_l_links;
	t_link *current_link;

	current = node->l_links;
	while (current)
	{
		other_node = ((t_link*)current->content)->terminal;
		other_node_l_links = other_node->l_links;
		while (other_node_l_links)
		{
			current_link = other_node_l_links->content;
			if (current_link->terminal == node)
			{
				dlist_erase(&((t_node*)current->content)->l_links, other_node_l_links);
				break ;
			}
			other_node_l_links = other_node_l_links->next;
		}
		current = current->next;
	}
	free_node(node);
}