/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:45:10 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/27 17:18:15 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

t_flow	*dinic_algo(int nb_ants, t_graph *graph)
{
	t_flow *flow;
	size_t max_theor_flow;

	max_theor_flow = find_theory_maxflow(nb_ants, graph);
	printf("max theorical flow : %lu\n", max_theor_flow);
	flow = create_tflow();
	if (!flow)
		return (0);
	while (flow->max_flow < max_theor_flow)
	{
		if (construct_level_graph(graph))
			break;
		// find_paths();
		// flow = create_flow();
		// int nbr_step = nbr_step_algo(flow, nb_ants);
		// nbr_step < current_nbr_step ?
		// TODO temporary
		break;
	}
	return (flow);
}