/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tflow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:30:53 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/01 18:03:16 by abourbou         ###   ########lyon.fr   */
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
	t_path	*path;
	t_node	*opp_node;
	t_dlist	*llink;
	t_link	*link;
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
		//! temp
		t_node *save = current_node;
		//! temp
		while (llink)
		{
			link = llink->content;
			opp_node = find_opposite_node(link, current_node);
			if (!is_node_accessible(link, current_node, opp_node))
			{
				current_node = opp_node;
				if (current_node->is_used == true)
					printf("ERROR NODE %s HAS ALREADY BEEN USED IN A PATH\n", current_node->name);
				else
					break;
			}
			llink = llink->next;
		}
		//! temp
		if (current_node == save)
			printf("ERROR THIS IS A DEAD END\n");
		if (current_node != end)
			current_node->is_used = true;
		//! temp
		if (path_insert(path, current_node))
		{
			printf("test4\n");
			free_path(path);
			return (0);
		}
		++length;
	}
	path->length = length;
	return (path);
}

void	display_path(t_path *path)
{
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
}

t_flow	*create_tflow(t_graph *graph)
{
	t_flow	*tflow;
	t_path	*path;
	t_dlist	*llink;
	t_link	*link;
	t_node	*opp_node;

	//! temp
	for (t_dlist *current = graph->l_node; current != 0; current = current->next)
	{
		t_node *node = current->content;
		node->is_used = false;
	}
	//! temp

	tflow = init_tflow();
	if (!tflow)
		return (0);
	llink = graph->start_node->l_links;
	int temp_flow = 0;
	while (llink)
	{
		link = llink->content;
		opp_node = find_opposite_node(link, graph->start_node);
		if (!is_node_accessible(link, graph->start_node, opp_node))
		{
			path = create_path(graph->start_node, graph->end_node, opp_node);
			if (!path)
			{
				printf("Error path\n");
				free_tflow(tflow);
				return (0);
			}
			display_path(path);
			// if (tflow_insert_path(tflow, path))
			// {
			// 	free_tflow(tflow);
			// 	return (0);
			// }
			temp_flow++;
		}
		llink = llink->next;
	}
	printf("nb paths : %d\n", temp_flow);
	return (tflow);
}