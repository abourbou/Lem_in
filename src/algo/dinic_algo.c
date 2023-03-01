/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:45:10 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/01 18:03:02 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

t_flow	*dinic_algo(t_graph *graph)
{

	size_t	max_theor_flow;
	size_t	current_flow;\
	t_flow	*tflow;

	max_theor_flow = find_theory_maxflow(graph);
	// save_tflow = 0;
	current_flow = 0;
	printf("max theorical flow : %lu\n", max_theor_flow);

	int i = 0;
	while (!current_flow || current_flow < max_theor_flow)
	{
		printf("\n***** %d iteration of Dinic Algo *****\n", i+1);
		if (construct_level_graph(graph))
		{
			printf("No more path possible\n");
			break;
		}
		//TODO Construct blocking path
		find_blocking_path(graph, &current_flow, max_theor_flow);
		// print_graph(graph);

		//* TODO later for optimize purpose
		//TODO Create flow of paths from graph
		//TODO Compute nb step from this flow and save it if better
		//TODO Repeat
		// ! temporary
		++i;
	}
	printf("Final flow is : %lu\n", current_flow);
	tflow = create_tflow(graph);
	if (!tflow)
	{
		print_error("can not create the t_flow");
		free_graph(graph);
		exit(1);
	}
	// return (save_tflow);
	return (tflow);
}