/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_to_graph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:50:29 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/24 13:31:00 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	reset_graph(t_graph *graph)
{
	graph->lnode = 0;
	graph->source = 0;
	graph->sink = 0;
}

short	create_nodes(t_data *data, t_graph *graph)
{
	t_vertex	*current_vertex;
	t_dlist		*current_node;
	t_dlist		*new_lnode;

	current_vertex = data->list_vertex;
	graph->lnode = dlist_new(convert_vertex_to_node(current_vertex));
	if (!graph->lnode)
		return (print_error_return("failed creating node\n", EXIT_FAILURE));
	current_vertex = current_vertex->next;
	current_node = graph->lnode;
	while (current_vertex)
	{
		new_lnode = dlist_new(convert_vertex_to_node(current_vertex));
		if (!new_lnode)
			return (print_error_return("failed creating node\n", EXIT_FAILURE));
		dlist_addafter(current_node, new_lnode);
		current_vertex = current_vertex->next;
		current_node = current_node->next;
	}
	return (EXIT_SUCCESS);
}

void	add_start_end(t_data *data, t_graph *graph)
{
	t_dlist	*lcurrent;
	char	*start_name;
	char	*end_name;
	t_node	*node;

	lcurrent = graph->lnode;
	start_name = data->start_vertex->name;
	end_name = data->end_vertex->name;
	while (lcurrent)
	{
		node = lcurrent->content;
		if (!ft_strcmp(start_name, node->name))
			graph->source = lcurrent->content;
		else if (!ft_strcmp(end_name, node->name))
			graph->sink = lcurrent->content;
		lcurrent = lcurrent->next;
	}
}

short	create_links(t_data *data, t_graph *graph)
{
	t_edge	*current_edge;
	t_node	*node1;
	t_node	*node2;

	current_edge = data->list_edge;
	while (current_edge)
	{
		if (!ft_strcmp(current_edge->vertex1, current_edge->vertex2))
			return (print_error_return("link with 2 times the same room\n",
					EXIT_FAILURE));
		if (find_nodes(current_edge, graph, &node1, &node2))
			return (print_error_return("link to unknown room\n", EXIT_FAILURE));
		if (check_edge_already_exist(node1, node2))
			return (print_error_return("link already exist\n", EXIT_FAILURE));
		if (create_link(node1, node2))
			return (print_error_return("malloc failed creating link\n",
					EXIT_FAILURE));
		current_edge = current_edge->next;
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
	return (EXIT_SUCCESS);
}
