/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:23:55 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/27 16:51:49 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

size_t	find_theory_maxflow(int nb_ants, t_graph *graph)
{
	size_t	max;
	size_t	nb_start;
	size_t	nb_end;

	max = nb_ants;
	nb_start = dlist_compt(graph->start_node->l_links);
	nb_end = dlist_compt(graph->end_node->l_links);
	if (nb_start < max)
		max = nb_start;
	if (nb_end < max)
		max = nb_end;
	return (max);
}

// Can the node be accessed from the link
// return EXIT_SUCCESS if it is the case
// or EXIT_FAILURE if it is blocked
short	can_access_node(t_link *link, t_node *head)
{
	if (head == link->node1 && link->flow != 1)
		return (EXIT_SUCCESS);
	else if (head == link->node2 && link->flow != -1)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
