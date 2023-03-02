/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_flow2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:41:44 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/02 15:42:31 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

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
