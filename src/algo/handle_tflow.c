/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tflow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:30:53 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/03 12:40:59 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

t_path	*init_path(t_node *start, t_node *end, t_node *current_node,
					unsigned int *length)
{
	t_path	*path;

	if (!start || !end || !current_node)
		return (0);
	path = malloc(sizeof(t_path));
	if (!path)
		return (0);
	path->l_start = 0;
	path->l_end = 0;
	if (path_insert(path, start))
		return (free_ret_path(path));
	if (path_insert(path, current_node))
		return (free_ret_path(path));
	*length = 1;
	return (path);
}

t_node	*find_next_node(t_node *current_node)
{
	t_dlist	*llink;
	t_link	*link;
	t_node	*opp_node;

	llink = current_node->l_links;
	while (llink)
	{
		link = llink->content;
		opp_node = find_opposite_node(link, current_node);
		if (!is_node_accessible(link, current_node, opp_node))
			return (opp_node);
		llink = llink->next;
	}
	return (0);
}

t_path	*create_path(t_node *start, t_node *end, t_node *current_node)
{
	t_path			*path;
	unsigned int	length;

	path = init_path(start, end, current_node, &length);
	if (!path)
		return (0);
	while (current_node != end)
	{
		current_node = find_next_node(current_node);
		if (current_node != current_node->node_out)
		{
			++length;
			if (path_insert(path, current_node))
				return (free_ret_path(path));
		}
	}
	if (path_insert(path, current_node))
		return (free_ret_path(path));
	path->length = length + 1;
	path->capacity = path->length;
	path->nbr_ants = 0;
	return (path);
}

t_flow	*free_ret_flow(t_flow *tflow, char *msg)
{
	print_error(msg);
	free_tflow(tflow);
	return (0);
}

t_flow	*create_tflow(t_graph *graph, t_flow *tflow)
{
	t_path	*path;
	t_dlist	*llink;
	t_link	*link;
	t_node	*opp_node;

	tflow = init_tflow();
	if (!tflow)
		return (0);
	llink = graph->start_node->l_links;
	while (llink)
	{
		link = llink->content;
		opp_node = find_opposite_node(link, graph->start_node);
		if (!is_node_accessible(link, graph->start_node, opp_node))
		{
			path = create_path(graph->start_node, graph->end_node, opp_node);
			if (!path)
				return (free_ret_flow(tflow, "can not create path"));
			if (tflow_insert_path(tflow, path))
				return (free_ret_flow(tflow, "can not insert path"));
		}
		llink = llink->next;
	}
	return (tflow);
}
