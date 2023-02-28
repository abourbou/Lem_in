/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_flow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:48:34 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/28 15:04:52 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

t_flow	*create_tflow(void)
{
	t_flow *flow;

	flow = malloc(sizeof(t_flow));
	if (!flow)
		return (0);
	flow->l_path = 0;
	flow->max_flow = 0;
	return (flow);
}

void	increment_flow(t_link *link, t_node *source, t_node *dest)
{
	int	val;
	if (link->node1 == source && link->node2 == dest)
		val = 1;
	else if (link->node2 == source && link->node1 == dest)
		val = -1;
	else
	{
		print_error("error incrementing flow");
		exit(1);
	}
	link->flow += val;
}