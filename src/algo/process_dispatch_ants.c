/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dispatch_ants.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:02:45 by sbaranes          #+#    #+#             */
/*   Updated: 2023/03/02 19:33:07 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

// TODO : SBR - kick ca a la fin
void	print_flow(t_flow *flow)
{
	int y = 1;
	for (t_dlist *cursor = flow->l_path; cursor; cursor = cursor->next)
	{
		int i = 0;
		y++;
		t_path	*current = cursor->content;
		for (t_dlist *lst_room = current->l_start; lst_room ; lst_room = lst_room->next)
		{
			t_node *room = lst_room->content;
			printf("Room %d : %s have and num %d\n", i, room->name, room->ant_nb);
			i++;
		}
		puts("");
	}
}

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

void	distib_in_path(t_flow *flow, unsigned int nb_ants)
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

void	dispatch_ants(t_flow *flow, unsigned int nb_ants)
{
	int	i;

	print_flow(flow);
	flow->ants_left = nb_ants;
	flow->path_necessary = check_path_to_use(flow, nb_ants);
	distib_in_path(flow, nb_ants);

	// TODO : SBR - kick ca a la fin
	puts("print flow\n");
	t_dlist	*cursor;
	cursor = flow->l_path;
	i = 0;
	while (cursor)
	{
		t_path	*current = cursor->content;
		printf("flow %d content %d ants for size = %d | real capacity = %d\n",
			i , current->nbr_ants, current->length, current->capacity);
		cursor = cursor->next;
		i++;
	}

	// TODO : SBR - kick ca a la fin
	printf("witc %d path is will take %d laps\n\n", flow->path_necessary, get_nb_laps(flow));

}
