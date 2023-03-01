/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ants_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:18:05 by sbaranes          #+#    #+#             */
/*   Updated: 2023/03/02 19:23:55 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"
#include "graph.h"

void	print_node(t_node *node)
{
	// TODO : SBR = peut etre a changer si pas printf
	printf("L%s-%d ", node->name, node->ant_nb);
}

t_dlist	*get_last_node_empty(t_path *path)
{
	// t_dlist	*cursor;
	// t_dlist	*last;
	// t_node	*node;

	// cursor = path->l_start->next;
	// while (cursor)
	// {
	// 	node = cursor->content;
	// 	if (node->ant_nb == 0)
	// 		last = cursor;
	// 	cursor = cursor->next;
	// }

	//TODO : SBR - mettre un pointeur sur le dernier fourmie .
	return path->l_end;
}

void	print_path(t_path *path)
{
	t_dlist	*cursor;
	t_node	*node;

	cursor = get_last_node_empty(path);
	node = cursor->content;
	// printf("show room name print_path  = %s | ants %d\n", node->name, node->ant_nb);
	while (cursor->prev)
	{
		node = cursor->content;
		if (node->ant_nb)
			print_node(node);
		cursor = cursor->prev;
	}
}

void	moove_all_by_one(t_flow *flow, t_path *path)
{
	t_dlist	*cursor;
	t_node	*node;
	t_node	*prev;

	cursor = get_last_node_empty(path);
	node = cursor->content;
	// printf("show room name moove_all  = %s | ants %d\n", node->name, node->ant_nb);
	while (cursor)
	{
		node = cursor->content;
		if (cursor == path->l_start)
			break;
		prev = cursor->prev->content;
		if (cursor == path->l_end && node->ant_nb != 0)
		{
			node->ant_nb = 0;
			flow->ants_distrub++;
		}
		else if (node->ant_nb == 0)
		{
			node->ant_nb = prev->ant_nb;
			prev->ant_nb = 0;
		}
		cursor = cursor->prev;
	}
}
