/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachabaranes <sachabaranes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:06:00 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/03 10:53:48 by sachabarane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "graph.h"
#include "queue.h"
#include "algo.h"

void	init_data(t_data *data)
{
	data->numb_ants = 0;
	data->start_vertex = NULL;
	data->end_vertex = NULL;
	data->dico_vertex = NULL;
	data->list_vertex = NULL;
	data->list_edge = NULL;
	data->list_map = NULL;
	data->pars.end = 0;
	data->pars.start = 0;
	data->pars.step = 1;
}

void	print_data(t_data *data)
{
	if (data->start_vertex != NULL)
		printf("start vertex = vertex : %s | cord x : %d | cord y : %d\n", data->start_vertex->name, data->start_vertex->cord_x, data->start_vertex->cord_y);
	if (data->end_vertex  != NULL)
		printf("end vertex = vertex : %s | cord x : %d | cord y : %d\n\n", data->end_vertex->name, data->end_vertex->cord_x, data->end_vertex->cord_y);

	printf("list vertex :\n");
	if (data->list_vertex)
		for (t_vertex *cursor = data->list_vertex; cursor; cursor = cursor->next)
		{
			printf("name of vertex : %s | cord x : %d | cord y : %d\n", cursor->name, cursor->cord_x, cursor->cord_y);
		}

	printf("\nlist edge :\n");
	for (t_edge *cursor = data->list_edge; cursor; cursor = cursor->next)
	{
		printf("edge 1 : %s | edge 2 : %s | direction x : %d\n", cursor->vertex1, cursor->vertex2, cursor->direction);
	}
}

void	print_graph(t_graph *graph)
{
	t_node *start_node = graph->start_node;
	t_node *end_node = graph->end_node;
	printf("start_node : %s, end_node : %s\n", start_node->name, end_node->name);

	t_dlist *current = graph->l_node;
	t_dlist *llast;
	while (current)
	{
		if (!current->next)
			llast = current;
		t_node *node = current->content;
		printf("node %s, level: %u\n", node->name, node->level);
		t_dlist *current_llink = node->l_links;
		while (current_llink)
		{
			t_link *link = current_llink->content;
			t_node *other_node = find_opposite_node(link, node);
			int flow = link->flow;
			if (link->node1 == node)
				printf("\t-> %s, flow : %d\n", other_node->name, flow);
			else
				printf("\t<- %s, flow : %d\n", other_node->name, flow);
			current_llink = current_llink->next;
		}
		current = current->next;
	}
	printf("backward : ");
	while (llast)
	{
		t_node *node = llast->content;
		printf("%s - ", node->name);
		llast = llast->prev;
	}
	printf("\n");
}

int	main(void)
{
	t_data	data;
	t_graph	graph;
	clock_t	start;
	t_flow *flow;

	init_data(&data);
	flow = NULL;
	pars_args(&data);
	if (convert_data_graph(&data, &graph))
	{
		free_graph(&graph);
		free_data(&data);
		return (EXIT_FAILURE);
	}
	free_data(&data);
	graph.nb_ants = data.numb_ants;
	if (check_path_exists(&graph))
	{
		print_error("No path exists from start to end\n");
		free_graph(&graph);
		return (EXIT_FAILURE);
	};
	flow = dinic_algo(&graph);
	dispatch_ants(flow, graph.nb_ants);
	run_ants_and_print_moove(flow, graph.nb_ants);
	free_tflow(flow);
	free_graph(&graph);
	return (0);
}
