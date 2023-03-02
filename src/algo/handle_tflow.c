/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tflow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:30:53 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/02 22:28:51 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

void	free_path(t_path *path)
{
	t_dlist	*current;
	t_dlist	*next;

	current = path->l_start;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(path);
}

short	path_insert(t_path *path, t_node *node)
{
	if (!path->l_start || !path->l_end)
	{
		path->l_start = dlist_new(node);
		if (!path->l_start)
			return (EXIT_FAILURE);
		path->l_end = path->l_start;
		return (EXIT_SUCCESS);
	}
	path->l_end->next = dlist_new(node);
	if (!path->l_end->next)
		return (EXIT_FAILURE);
	path->l_end->next->prev = path->l_end;
	path->l_end = path->l_end->next;
	return (EXIT_SUCCESS);
}

t_path	*create_path(t_node *start, t_node *end, t_node *current_node)
{
	t_path			*path;
	t_node			*opp_node;
	t_dlist			*llink;
	t_link			*link;
	unsigned int	length;

	if (!start || !end || !current_node)
		return (0);
	path = malloc(sizeof(t_path));
	if (!path)
		return (0);
	path->l_start = 0;
	path->l_end = 0;
	if (path_insert(path, start))
	{
		free_path(path);
		return (0);
	}
	if (path_insert(path, current_node))
	{
		free_path(path);
		return (0);
	}
	length = 1;
	while (current_node != end)
	{
		llink = current_node->l_links;
		while (llink)
		{
			link = llink->content;
			opp_node = find_opposite_node(link, current_node);
			if (!is_node_accessible(link, current_node, opp_node))
			{
				current_node = opp_node;
				break ;
			}
			llink = llink->next;
		}
		if (current_node != current_node->node_out)
		{
			++length;
			if (path_insert(path, current_node))
			{
				free_path(path);
				return (0);
			}
		}
	}
	if (path_insert(path, current_node))
	{
		free_path(path);
		return (0);
	}
	path->length = length + 1;
	path->capacity = path->length;
	return (path);
}

void	display_path(t_path *path)
{
	printf("path length : %d, nb : %d, path_capacity : %d\n", path->length, path->nbr_ants, path->capacity);
	printf("right sens : ");
	t_dlist *it = path->l_start;
	while (it)
	{
		t_node *node = it->content;
		printf("%s - ", node->name);
		it = it->next;
	}
	printf("\n");
	printf("reverse sens : ");
	it = path->l_end;
	while (it)
	{
		t_node *node = it->content;
		printf("%s - ", node->name);
		it = it->prev;
	}
	printf("\n");
	printf("\n");
}

void	display_flow(t_flow *tflow)
{
	t_dlist *lpath = tflow->l_path;
	while (lpath)
	{
		t_path *path = lpath->content;
		display_path(path);
		// printf("path length : %u\n", path->length);
		lpath = lpath->next;
	}
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
	// printf("nbr path : %lu\n", tflow->max_flow);
	display_flow(tflow);
	return (tflow);
}
