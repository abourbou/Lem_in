/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_flow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:48:34 by abourbou          #+#    #+#             */
/*   Updated: 2023/03/03 11:34:00 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

t_flow	*init_tflow(void)
{
	t_flow	*tflow;

	tflow = malloc(sizeof(t_flow));
	if (!tflow)
	{
		print_error("can not malloc in create_tflow");
		return (0);
	}
	tflow->l_path = 0;
	tflow->max_flow = 0;
	return (tflow);
}

void	free_tflow(t_flow *tflow)
{
	t_dlist	*l_path;
	t_dlist	*l_next_path;
	t_path	*path;
	t_dlist	*l_current_room;
	t_dlist	*l_next_room;

	l_path = tflow->l_path;
	while (l_path)
	{
		path = l_path->content;
		l_current_room = path->l_start;
		while (l_current_room)
		{
			l_next_room = l_current_room->next;
			free(l_current_room);
			l_current_room = l_next_room;
		}
		free(path);
		l_next_path = l_path->next;
		free(l_path);
		l_path = l_next_path;
	}
	free(tflow);
}

void	increment_flow(t_link *link, t_node *source, t_node *dest)
{
	int	val;

	if (link->node1 == source && link->node2 == dest)
		val = 1;
	else if (link->node2 == source && link->node1 == dest)
		val = -1;
	else
	{
		print_error("error incrementing flow");
		exit(1);
	}
	link->flow += val;
}
