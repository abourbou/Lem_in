/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:06:00 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/03 13:07:31 by abourbou         ###   ########lyon.fr   */
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

int	free_graph_data(t_graph *graph, t_data *data)
{
	free_data(data);
	free_graph(graph);
	return (EXIT_FAILURE);
}

int	main(void)
{
	t_data	data;
	t_graph	graph;
	t_flow	*flow;

	init_data(&data);
	pars_args(&data);
	if (convert_data_graph(&data, &graph))
		return (free_graph_data(&graph, &data));
	graph.nb_ants = data.numb_ants;
	if (check_path_exists(&graph))
	{
		print_error("No path exists from start to end\n");
		free_graph_data(&graph, &data);
		return (EXIT_FAILURE);
	}
	print_map(data.list_map);
	free_data(&data);
	flow = dinic_algo(&graph);
	run_ants_and_print(flow, graph.nb_ants);
	free_tflow(flow);
	free_graph(&graph);
	return (0);
}
