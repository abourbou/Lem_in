/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dispatch_ants.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:02:45 by sbaranes          #+#    #+#             */
/*   Updated: 2023/03/03 12:49:57 by sbaranes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

unsigned int	soustrack_ants(unsigned int rest_ant, unsigned int capacity)
{
	int	res;

	res = 0;
	if (rest_ant > capacity)
		res = capacity - rest_ant;
	else if (capacity < rest_ant)
		res = rest_ant - capacity;
	if (res < 0)
		res *= -1;
	return (res);
}

void	distib_in_path(t_flow *flow, unsigned int nb_ants)
{
	unsigned int	i;
	t_dlist			*cursor;
	t_path			*current;
	t_path			*current_next;

	i = 0;
	while (i < nb_ants)
	{
		cursor = flow->l_path;
		while (cursor->next)
		{
			current = cursor->content;
			current_next = cursor->next->content;
			if (distib_in_path_suite(current, current_next))
				break ;
			cursor = cursor->next;
		}
		if (!cursor->next)
		{
			current = cursor->content;
			current->nbr_ants++;
		}
		i++;
	}
}

void	get_path_necessary(t_flow *flow)
{
	t_dlist	*cursor;
	t_path	*current;

	flow->path_necessary = 0;
	cursor = flow->l_path;
	while (cursor)
	{
		current = cursor->content;
		if (current->nbr_ants > 0)
			flow->path_necessary++;
		cursor = cursor->next;
	}
}

void	reset_flow_nb_ant(t_flow *flow)
{
	t_dlist	*cursor;
	t_path	*current;

	cursor = flow->l_path;
	while (cursor)
	{
		current = cursor->content;
		current->nbr_ants = 0;
		cursor = cursor->next;
	}
}

void	dispatch_ants(t_flow *flow, unsigned int nb_ants)
{
	reset_flow_nb_ant(flow);
	flow->ants_left = nb_ants;
	distib_in_path(flow, nb_ants);
	flow->nb_prev = get_nb_laps(flow);
	get_path_necessary(flow);
}
