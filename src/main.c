/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:06:00 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/31 17:07:31 by sbaranes         ###   ########.fr       */
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

void	check_direct_path(t_graph *graph)
{
	t_dlist			*llink;
	t_link			*link;
	unsigned int	i;

	i = 0;
	llink = graph->start_node->l_links;
	while (llink)
	{
		link = llink->content;
		if (find_opposite_node(link, graph->start_node) == graph->end_node)
		{
			while (i < graph->nb_ants)
			{
				graph->end_node->ant_nb = i + 1;
				print_node(graph->end_node);
				i++;
			}
			ft_putstr("\033[3;34m\nNumbers laps : \033[1;32m 1 \033[0m\n");
			free_graph(graph);
			exit(0);
		}
		llink = llink->next;
	}
	return ;
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
	check_direct_path(&graph);
	flow = dinic_algo(&graph);
	run_ants_and_print(flow, graph.nb_ants);
	free_tflow(flow);
	free_graph(&graph);
	return (0);
}
