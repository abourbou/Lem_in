/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:06:00 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/24 13:13:12 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "graph.h"

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
	t_node *source = graph->source->content;
	t_node *sink = graph->sink->content;
	printf("source : %s, sink : %s\n", source->name, sink->name);

	t_dlist *current = graph->lnode;
	while (current)
	{
		t_node *node = current->content;
		printf("node %s\n", node->name);
		t_dlist *current_llink = node->l_links;
		while (current_llink)
		{
			t_link *link = current_llink->content;
			printf("\t- link with %s\n", link->terminal->name);
			current_llink = current_llink->next;
		}
		current = current->next;
	}
}

int	main(void)
{
	t_data	data;
	t_graph	graph;
	clock_t	start;
	double	cpu_time_used;

	init_data(&data);

	start = clock();
	pars_args(&data);
	cpu_time_used = (double)(clock() - start) / CLOCKS_PER_SEC;
	printf("pars_args took %lfs\n", cpu_time_used);

	start = clock();
	if (convert_data_graph(&data, &graph))
	{
		free_data(&data);
		print_error("Error converting the data to a graph");
		return (EXIT_FAILURE);
	}
	cpu_time_used = (double)(clock() - start) / CLOCKS_PER_SEC;
	printf("convert_data_graph took %lfs\n", cpu_time_used);

	// print_data(&data);
	print_map(data.list_map);
	free_data(&data);
	// print_graph(&graph);
	//TODO check if a path exist between source and sink
	//TODO erase node with less or equal to 1 link for opti purpose

	return(EXIT_SUCCESS);
}
