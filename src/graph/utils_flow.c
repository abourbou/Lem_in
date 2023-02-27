/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_flow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:48:34 by abourbou          #+#    #+#             */
/*   Updated: 2023/02/27 12:29:54 by abourbou         ###   ########lyon.fr   */
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