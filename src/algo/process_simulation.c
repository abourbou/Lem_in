/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachabaranes <sachabaranes@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:03:24 by sbaranes          #+#    #+#             */
/*   Updated: 2023/03/02 21:10:09 by sachabarane      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"

static void	put_new_ant(t_flow *flow)
{
	static int	i = 1;
	int			nb_path_used;
	t_dlist		*cursor;
	t_path		*current;
	t_node		*node;

	cursor = flow->l_path;
	nb_path_used = flow->path_necessary;
	while (cursor && flow->ants_left != 0 && nb_path_used != 0)
	{
		current = cursor->content;
		node = current->l_start->next->content;
		if (current->nbr_ants != 0)
		{
			node->ant_nb = i;
			i++;
			current->nbr_ants--;
			flow->ants_left--;
			print_node(node);
		}
		nb_path_used--;
		cursor = cursor->next;
	}
}

static void	moove_other_ants(t_flow *flow)
{
	int		nb_path_used;
	t_dlist	*cursor;
	t_path	*current;

	nb_path_used = flow->path_necessary;
	cursor = flow->l_path;
	while (cursor && nb_path_used != 0)
	{
		current = cursor->content;
		moove_all_by_one(flow, current);
		nb_path_used--;
		cursor = cursor->next;
	}
}

void	run_ants_and_print_moove(t_flow *flow, unsigned int ants_nb)
{
	bool	in_progress;

	in_progress = true;
	flow->ants_left = ants_nb;
	flow->ants_distrub = 0;
	while (in_progress)
	{
		// puts("\n\n NEW TURN \n\n");
		// print_flow(flow);
		// puts("befor moove");
		moove_other_ants(flow);
		// puts("afther moove");
		// print_flow(flow);
		// puts("befor put_new_ant");
		put_new_ant(flow);
		// puts("afther put_new_ant");
		// printf("DEBUG : %d | %d | %d \n",flow->ants_distrub , ants_nb, flow->ants_left);
		if (flow->ants_distrub == ants_nb)
			in_progress = false;
		ft_putstr("\n");
	}
}
