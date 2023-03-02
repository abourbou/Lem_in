/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dispatch_ants.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachabaranes <sachabaranes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:02:45 by sbaranes          #+#    #+#             */
/*   Updated: 2023/03/02 21:18:00 by sachabarane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

static void	dispatch_last_ants(t_flow *flow, unsigned int nb_ants)
{
	t_dlist	*cursor;
	t_path	*current;

	cursor = flow->l_path;
	while (nb_ants != 0)
	{
		current = cursor->content;
		current->nbr_ants++;
		nb_ants--;
		if (!cursor->next)
			cursor = flow->l_path;
		else
			cursor = cursor->next;
	}
}

static int	check_path_to_use(t_flow *flow, unsigned int nb_ants)
{
	int				path_necessary;
	unsigned int	rest_ant;
	t_dlist			*cursor;
	t_path			*current;

	path_necessary = 0;
	rest_ant = nb_ants;
	cursor = flow->l_path;
	while (cursor && rest_ant != 0)
	{
		current = cursor->content;
		path_necessary++;
		if (current->capacity < rest_ant)
			resize_capacity(flow, cursor, current);
		if (set_roolback(flow, cursor, current))
			check_path_to_use(flow, nb_ants);
		if (current->capacity <= rest_ant)
			rest_ant = rest_ant - current->capacity;
		cursor = cursor->next;
	}
	return (path_necessary);
}

static void	distib_in_path(t_flow *flow, unsigned int nb_ants)
{
	unsigned int		i;
	unsigned int		nb_path_used;
	t_dlist				*cursor;
	t_path				*current;

	i = 0;
	cursor = flow->l_path;
	nb_path_used = flow->path_necessary;
	while (i < nb_path_used)
	{
		current = cursor->content;
		while (current->capacity > current->nbr_ants && nb_ants != 0)
		{
			current->nbr_ants++;
			nb_ants--;
		}
		i++;
		cursor = cursor->next;
	}
	dispatch_last_ants(flow, nb_ants);
}

int	get_nb_laps(t_flow *flow)
{
	t_path	*current;

	current = flow->l_path->content;
	return (current->nbr_ants + current->length - 1);
}

void	dispatch_ants(t_flow *flow, unsigned int nb_ants)
{
	flow->ants_left = nb_ants;
	flow->path_necessary = check_path_to_use(flow, nb_ants);
	distib_in_path(flow, nb_ants);
	flow->nb_prev = get_nb_laps(flow);
	int i = 0;
	printf("nb fourmie = %d\n\n", flow->ants_left);
	for (t_dlist *cursor = flow->l_path; cursor; cursor = cursor->next)
	{
		t_path	*current = cursor->content;
		printf("path %d = %d ants | size %d | capasity %d", i, current->nbr_ants,
				current->length, current->capacity);
		puts("");
		i++;
	}
	printf("resulte nb tour  = %d\n", get_nb_laps(flow));
}

	/**
	 * juste a decalere en haut si besoin debug
	 * int i = 0;
	 * printf("nb fourmie = %d\n", flow->ants_left);
	 * for (t_dlist *cursor = flow->t_path; cursor; cursor = cursor->next)
	 * {
	 * 	t_path	*current = cursor->content;
	 * 	printf("path %d = %d ants | size %d | capasity%d", i, current->nbr_ants,
	 * 			current->length, current->capacity);
	 * 	puts("");
	 * 	i++;
	 * }
	 * printf("resulte nb tour  = %d\n", get_nb_laps(flow));
	**/
