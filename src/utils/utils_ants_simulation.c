/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ants_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbaranes <sbaranes@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:18:05 by sbaranes          #+#    #+#             */
/*   Updated: 2023/03/31 17:06:35 by sbaranes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

void	print_node(t_node *node)
{
	ft_putstr("\033[0mL\e[1;34m");
	ft_putnbr(node->ant_nb);
	ft_putstr("\033[0m-\e[1;36m");
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

void	move_all_by_one(t_flow *flow, t_path *path)
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
