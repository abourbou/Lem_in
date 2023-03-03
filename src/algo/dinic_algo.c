/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:45:10 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/03 12:32:14 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

t_flow	*dinic_algo(t_graph *graph)
{
	size_t	max_theor_flow;
	size_t	current_flow;
	t_flow	*tflow;
	t_flow	*buffer_tflow;

	max_theor_flow = find_theory_maxflow(graph);
	current_flow = 0;
	tflow = 0;
		while (!current_flow || current_flow < max_theor_flow)
	{
		if (construct_level_graph(graph))
			break ;
		find_blocking_path(graph, &current_flow, max_theor_flow);
		buffer_tflow = create_tflow(graph, 0);
		dispatch_ants(buffer_tflow, graph->nb_ants);
		buffer_tflow->nb_step = get_nb_laps(buffer_tflow);
		if (!tflow)
			tflow = buffer_tflow;
		else
		{
			if (tflow->nb_step <= 0 || tflow->nb_step > buffer_tflow->nb_step)
			{
				free_tflow(tflow);
				tflow = buffer_tflow;
			}
			else
				free_tflow(buffer_tflow);
		}
	}
	if (!tflow)
		tflow = create_tflow(graph, 0);
	if (!tflow)
	{
		print_error("can not create the t_flow");
		free_graph(graph);
		exit(1);
	}
	return (tflow);
}
