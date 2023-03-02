/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ants_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:18:05 by sbaranes          #+#    #+#             */
/*   Updated: 2023/03/02 19:44:11 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

void	print_node(t_node *node)
{
	ft_putstr("L");
	ft_putnbr(node->ant_nb);
	ft_putstr("-");
	ft_putstr(node->name);
	ft_putstr(" ");
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
		cursor = cursor->prev;
	}
}

void	process_last_node(t_flow *flow, t_node *node, t_node *prev)
{
	node->ant_nb = prev->ant_nb;
	prev->ant_nb = 0;
	if (node->ant_nb != 0)
	{
		print_node(node);
		flow->ants_distrub++;
		node->ant_nb = 0;
	}
}

void	moove_all_by_one(t_flow *flow, t_path *path)
{
	t_dlist	*cursor;
	t_node	*node;
	t_node	*prev;

	cursor = path->l_end;
	node = cursor->content;
	while (cursor)
	{
		node = cursor->content;
		if (cursor == path->l_start)
			break ;
		prev = cursor->prev->content;
		if (cursor != path->l_end)
		{
			node->ant_nb = prev->ant_nb;
			prev->ant_nb = 0;
		}
		else if (cursor == path->l_end)
			process_last_node(flow, node, prev);
		if (node->ant_nb != 0)
			print_node(node);
		cursor = cursor->prev;
	}
}
