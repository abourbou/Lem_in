/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:45:10 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/02 21:32:02 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

t_flow	*dinic_algo(t_graph *graph)
{
	size_t	max_theor_flow;
	size_t	current_flow;
	t_flow	*tflow;

	max_theor_flow = find_theory_maxflow(graph);
	printf("max theorical flow : %lu\n", max_theor_flow);
	current_flow = 0;
	while (!current_flow || current_flow < max_theor_flow)
	{
		if (construct_level_graph(graph))
			break ;
		find_blocking_path(graph, &current_flow, max_theor_flow);
	}
	printf("flow : %lu\n", current_flow);
	tflow = create_tflow(graph, 0);
	if (!tflow)
	{
		print_error("can not create the t_flow");
		free_graph(graph);
		exit(1);
	}
	return (tflow);
}
