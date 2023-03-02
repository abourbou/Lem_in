/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:00:27 by sachabarane       #+#    #+#             */
/*   Updated: 2023/03/02 19:33:14 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	resize_capacity(t_flow *flow, t_dlist *cursor, t_path *current)
{
	t_path	*next;

	if (cursor->next != NULL)
	{
		next = cursor->next->content;
		if ((current->capacity + 1) != flow->ants_left)
			current->capacity = next->capacity;
	}
}

bool	set_roolback(t_flow *flow, t_dlist *cursor, t_path *current)
{
	t_path	*prev;
	if (cursor->prev != NULL)
	{
		prev = cursor->prev->content;
		if (prev->capacity < current->capacity)
		{
			if (flow->ants_left >= (prev->capacity + current->capacity))
			{
				prev->capacity = current->capacity;
				return (true);
			}
		}
	}
	return (false);
}

int	get_nb_laps(t_flow *flow)
{
	t_path	*current;

	current = flow->l_path->content;
	return (current->nbr_ants + current->length);
}
