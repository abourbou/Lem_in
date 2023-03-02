/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_to_graph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:50:29 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/02 14:31:48 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

short	create_nodes(t_data *data, t_graph *graph)
{
	t_vertex	*current_vertex;
	t_dlist		*new_lnode;

	current_vertex = data->list_vertex;
	while (current_vertex)
	{
		new_lnode = dlist_new(convert_vertex_to_node(current_vertex->name));
		if (!new_lnode)
			return (print_error_return("failed creating node\n", EXIT_FAILURE));
		dlist_pushfront(&graph->l_node, new_lnode);
		current_vertex = current_vertex->next;
	}
	return (EXIT_SUCCESS);
}

void	add_start_end(t_data *data, t_graph *graph)
{
	t_dlist	*lcurrent;
	char	*start_name;
	char	*end_name;
	t_node	*node;

	lcurrent = graph->l_node;
	start_name = data->start_vertex->name;
	end_name = data->end_vertex->name;
	while (lcurrent)
	{
		node = lcurrent->content;
		if (!ft_strcmp(start_name, node->name))
			graph->start_node = lcurrent->content;
		else if (!ft_strcmp(end_name, node->name))
			graph->end_node = lcurrent->content;
		lcurrent = lcurrent->next;
	}
	graph->start_node->node_out = graph->start_node;
	graph->end_node->node_out = graph->end_node;
}

short	create_links(t_data *data, t_graph *graph)
{
	t_edge	*current_edge;
	t_node	*node1;
	t_node	*node2;

	current_edge = data->list_edge;
	while (current_edge)
	{
		if (find_nodes(current_edge, graph, &node1, &node2))
			return (print_error_return("link to unknown room\n", EXIT_FAILURE));
		if (check_link_already_exist(graph, node1, node2))
			return (print_error_return("link already exist\n", EXIT_FAILURE));
		if (create_unique_room_link(graph, node1, node2))
			return (print_error_return("malloc failed creating link\n",
					EXIT_FAILURE));
		current_edge = current_edge->next;
	}
	return (EXIT_SUCCESS);
}

short	add_node_out(t_graph *graph)
{
	t_dlist	*lnode;
	t_node	*node;
	t_dlist	*new_lnode;

	lnode = graph->l_node;
	while (lnode)
	{
		node = lnode->content;
		if (node != graph->start_node && node != graph->end_node
			&& node->node_out && node != node->node_out)
		{
			new_lnode = dlist_new(node->node_out);
			if (!new_lnode)
				return (EXIT_FAILURE);
			dlist_pushafter(lnode, new_lnode);
		}
		lnode = lnode->next;
	}
	return (EXIT_SUCCESS);
}

short	convert_data_graph(t_data *data, t_graph *graph)
{
	reset_graph(graph);
	if (create_nodes(data, graph))
		return (EXIT_FAILURE);
	add_start_end(data, graph);
	if (create_links(data, graph))
		return (EXIT_FAILURE);
	if (add_node_out(graph))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
