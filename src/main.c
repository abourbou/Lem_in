/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:06:00 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/03 10:53:38 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "graph.h"
#include "queue.h"
#include "algo.h"

void	print_flow(t_flow *flow)
{
	// int y = 1;
	// for (t_dlist *cursor = flow->l_path; cursor; cursor = cursor->next)
	// {
	// 	int i = 0;
	// 	y++;
	// 	t_path	*current = cursor->content;
	// 	for (t_dlist *lst_room = current->l_start; lst_room ; lst_room = lst_room->next)
	// 	{
	// 		t_node *room = lst_room->content;
	// 		printf("Room %d : %s have and num %d\n", i, room->name, room->ant_nb);
	// 		i++;
	// 	}
	// 	puts("");
	// }

	int y = 1;
	for (t_dlist *cursor = flow->l_path; cursor; cursor = cursor->next)
	{
		int i = 0;
		y++;
		t_path	*current = cursor->content;
		for (t_dlist *lst_room = current->l_end; lst_room ; lst_room = lst_room->prev)
		{
			t_node *room = lst_room->content;
			printf("Room %d : %s have and num %d\n", i, room->name, room->ant_nb);
			i++;
		}
		puts("");
	}
}

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

# define START_CLOCK(start) {start = clock();}
# define EVALUATE_CLOCK(start, name) {double cpu_time_used = (double)(clock() - start) / CLOCKS_PER_SEC; \
										printf("%s took %lfs\n", name, cpu_time_used);}

int	main(void)
{
	t_data	data;
	t_graph	graph;
	clock_t	start;

	init_data(&data);

	START_CLOCK(start);
	pars_args(&data);
	EVALUATE_CLOCK(start, "pars_args");

	START_CLOCK(start);
	if (convert_data_graph(&data, &graph))
	{
		free_graph(&graph);
		free_data(&data);
		return (EXIT_FAILURE);
	}
	free_data(&data);
	graph.nb_ants = data.numb_ants;
	EVALUATE_CLOCK(start, "convert_data_graph");

	START_CLOCK(start);
	if (check_path_exists(&graph))
	{
		print_error("No path exists from start to end\n");
		free_graph(&graph);
		return (EXIT_FAILURE);
	};
	EVALUATE_CLOCK(start, "preprocessing algo");
	// print_graph(&graph);

	START_CLOCK(start);
	t_flow *flow = dinic_algo(&graph);
	EVALUATE_CLOCK(start, "Dinic algorithm");

	START_CLOCK(start);
	flow->nb_prev = 0;
	dispatch_ants(flow, graph.nb_ants);
	run_ants_and_print_moove(flow, graph.nb_ants);
	EVALUATE_CLOCK(start, "dispatch_ants");

	printf("\n\n nb tour prevue = %d\n", flow->nb_prev);
	free_tflow(flow);
	free_graph(&graph);
	return (0);
}
