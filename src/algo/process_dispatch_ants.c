/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dispatch_ants.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:46:52 by sachabarane       #+#    #+#             */
/*   Updated: 2023/03/02 19:16:08 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

void	print_flow(t_flow *flow)
{
	puts("test flow\n");
	int y = 1;
	for (t_dlist *cursor = flow->l_path; cursor; cursor = cursor->next)
	{
		printf("Path num %d : \n", y);
		int i = 0;
		y++;
		t_path	*current = cursor->content;
		for (t_dlist *lst_room = current->l_start; lst_room ; lst_room = lst_room->next)
		{
			t_node *room = lst_room->content;
			printf("Room %d : %s\n", i,room->name);
			i++;
		}
		puts("");
	}
}

int	check_path_to_use(t_flow *flow, unsigned int nb_ants)
{
	int	nb_path_to_use;

	nb_path_to_use = 1;
	t_dlist *cursor = flow->l_path;
	while (cursor && nb_ants != 0)
	{
		t_path	*current = cursor->content;
		if (current->length <= nb_ants)
		{
			if (current->length == nb_ants)
				break;
			if (cursor->next != NULL)
			{
				t_path	*next = cursor->next->content;
				nb_ants = (nb_ants - (current->length + (next->length - current->length)));
			}
			else
				nb_ants = (nb_ants - current->length);
		}
		else if (current->length > nb_ants )
			break;
		if (nb_ants == 0)
			break ;
		nb_path_to_use++;
		cursor = cursor->next;
	}
	return (nb_path_to_use);
}

// void	distibute_last_ants(t_flow *flow, unsigned int nb_ants)
// {

// }

void	dispatch_ants(t_flow *flow, int nb_ants)
{
	print_flow(flow);
	puts("dispatch_ants start\n");

	// fonction pour le remplisage des paths :
	// option 1 renvoyer un tableau d'int qui va permettre de savoir combien
	// de fourmie on va envoye par chemin

	int nb_path_used = check_path_to_use(flow, nb_ants);
	printf("nb_path_used %d for %d ants\n", nb_path_used , nb_ants);

	int i = 0;
	t_dlist	*cursor;
	t_path	*current;

	cursor = flow->l_path;
	while (i < nb_path_used)
	{
		current = cursor->content;
		current->real_capasity_ants = current->length;
		if (cursor->next != NULL && i < nb_path_used - 1)
		{
			t_path	*next = cursor->next->content;
			current->real_capasity_ants = current->length + (next->length - current->length);
			printf("real_capasity_ants for path num %d = %d\n", i, current->real_capasity_ants);
		}
		while (current->real_capasity_ants > current->nbr_ants && nb_ants != 0)
		{
			current->nbr_ants++;
			nb_ants--;
		}
		printf("path nb %d = %d nb of ants\n", i, current->nbr_ants);
		i++;
		cursor = cursor->next;
	}
	printf("nm ants rest = %d\n", nb_ants);
	// distibute_last_ants(flow, nb_ants);
	// printf("nm ants rest final = %d\n", nb_ants);
	// for (size_t i = 0; i < count; i++)
	// {
	// 	/* code */
	// }

}
