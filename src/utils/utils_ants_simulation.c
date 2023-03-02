/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ants_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:18:05 by sbaranes          #+#    #+#             */
/*   Updated: 2023/03/02 19:33:17 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

void	print_node(t_node *node)
{
	// TODO : SBR = peut etre a changer si pas printf
	printf("L%d-%s ", node->ant_nb, node->name);
}

void	print_path(t_path *path)
{
	t_dlist	*cursor;
	t_node	*node;

	cursor = path->l_end;
	node = cursor->content;
	while (cursor)
	{
		node = cursor->content;
		if (node->ant_nb != 0)
			print_node(node);
		cursor = cursor->next;
	}
}

void	moove_all_by_one(t_flow *flow, t_path *path)
{
	t_dlist	*cursor;
	t_node	*node;
	t_node	*prev;

	cursor = path->l_end;
	node = cursor->content;
	// printf("show room name moove_all  = %s | ants %d\n", node->name, node->ant_nb);
	while (cursor)
	{
		node = cursor->content;
		if (cursor == path->l_start)
			break ;
		prev = cursor->prev->content;
		if (cursor == path->l_end)
		{
			node->ant_nb = 0;
			flow->ants_distrub++;
		}
		if (node->ant_nb == 0 && cursor != path->l_end)
		{
			node->ant_nb = prev->ant_nb;
			prev->ant_nb = 0;
		}
		cursor = cursor->prev;
	}
}
